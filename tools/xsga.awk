BEGIN {
  nobj = 0;
  id = -1;
  parent = -1;
  class = "";
  type = "";
  name = "";
  nconn = 0;
  dests[0] = "";
  sources[0] = "";
  children = "";
  verbose = 0;
  defline = 0;
  final_print = 1;
  noid = 1;
  sorttrace = 1;

  if (length(outnamebase) == 0) {
    outnamebase = "scene";
  }
}
#
END {
# Store and print final object
  if (id >= 0) {
    db_store_object(nobj);

    if (final_print == 0) {
      db_print_object(nobj);
    }

    nobj++;
  }

  printf("Total number of objects: %d\n", nobj);

  if (final_print) {
    for (i = 0; i < nobj; i++) {
      db_print_object(i, 0);
    }
  }

  if (sorttrace)
    outcmd = sprintf("sort > %s-conns.txt", outnamebase);
  else
    outcmd = sprintf("cat > %s-conns.txt", outnamebase);
    
# Print all the connection traces (still just explicit traces)
  for (i = 0; i < nobj; i++) {
    nconn = int(nconn_db[i]);

    for (j = 0; j < nconn; j++) {
      source = sources_db[i,j];

      while (length(source) > 0) {
	first = source;
	source = source_trace[source];
      }

      cdone = cdone_db[first];

      if (!cdone) {
	resolve_connector(first);
	trace = sprintf("%s(%s).%s", cclass, cname, cfield);
	printf("%s", trace) |& outcmd;
	cdone_db[first] = 1;
	print_dest_trace(first, 1, trace, 1);
      }
    }
  }

# Print all reverse connections
# Engines are listed in reverse order, traced bwds from a node.

  outcmd = sprintf("%s-bwdconns.txt", outnamebase);
  lastnode = -1;
  nbwdconn = 0;

  for (i = 0; i < nobj; i++) {
    nconn = int(nconn_db[i]);
    curobjid = object_db[i];

    if (type_db[i] == "node") {
      isnode = 1
      lastnode = curobjid;
    }
    else {
      isnode = 0;
    }
    
    for (j = 0; j < nconn; j++) {
      source = sources_db[i,j];
      dest = dests_db[i,j];

      resolve_connector(source);
      sfield = cfield;
      sidx = cidx;
      sobjid = cobjid;
      sclass = cclass;
      sname = cname;

      resolve_connector(dest);

# Is destination a node or engine?
      if (type_db[sidx] == "node") {
	if (type_db[cidx] == "node") {
	  # Node to Node
	  if (sobjid >= cobjid) {
	    nbwdconn++;
	    printf("%s[%s](%s)#%d#.%s -> %s[%s](%s)#%d#.%s\n",
		   sclass, type_db[sidx], sname, sobjid, sfield,
		   cclass, type_db[cidx], cname, cobjid, cfield) >> outcmd;
	  }
	}
	else {
	  # Node to Engine 
	  if (sobjid >= cobjid ||
	      (lastnode <= sobjid && sobjid <= cobjid)) {
	    nbwdconn++;
	    printf("%s[%s](%s)#%d#.%s -> %s[%s](%s)#%d#.%s\n",
		   sclass, type_db[sidx], sname, sobjid, sfield,
		   cclass, type_db[cidx], cname, cobjid, cfield) >> outcmd;
	  }
	}
      }
      else {
	if (type_db[cidx] == "node") {
	  # Engine to Node: Always OK....
	}
	else {
	  # Engine to Engine 
	  if (sobjid <= cobjid) {
	    nbwdconn++;
	    printf("%s[%s](%s)#%d#.%s -> %s[%s](%s)#%d#.%s\n",
		   sclass, type_db[sidx], sname, sobjid, sfield,
		   cclass, type_db[cidx], cname, cobjid, cfield) >> outcmd;
	  }
	}
      }
    }
  }

  if (nbwdconn > 0) {
    printf("Total number of backward connections: %d\n", nbwdconn) >> outcmd;
  }
}
#
# Functions
# ---------
function db_store_object(objidx, i)
{
  objidx_db[id] = objidx;
  object_db[objidx] = id;
  tree_db[objidx] = children;
  parent_db[objidx] = parent;
  class_db[objidx] = class;
  type_db[objidx] = type;
  name_db[objidx] = name;
  nconn_db[objidx] = nconn;

  for (i = 0; i < nconn; i++) {
    dests_db[objidx,i] = dests[i];
    sources_db[objidx,i] = sources[i];
  }
}
#
function db_print_object(objidx, i)
{
  id = object_db[objidx];
  children = tree_db[objidx];
  parent = parent_db[objidx];
  class = class_db[objidx];
  type = type_db[objidx];
  name = name_db[objidx];
  nconn = nconn_db[objidx];

  for (i = 0; i < nconn; i++) {
    dests[i] = dests_db[objidx,i];
    sources[i] = sources_db[objidx,i];
  }

  if (noid)
    _print_object_without_id();
  else
    _print_object_with_id();
}
#
function _print_object_with_id(i)
{
  if (length(name) > 0) {
    printf("XNAMED %d %s %s %s\n", id, type, class, name);
  }
  else {
    printf("XUNNAMED %d %s %s\n", id, type, class);
  }

  if (verbose > 0) {
    printf("% 5d : %s = %s\n", id, type, class);
    
    if (length(name) > 0) {
      printf("        name: %s\n", name);
    }

    if (length(children) > 0) {
      if (parent != id) {
	printf("  === WARNING! Parent and Node ID doesn't match ===\n");
      }

      printf("        children: %s\n", children);
    }

    if (nconn > 0) {
      printf("        connections...\n");

      for (i = 0; i < nconn; i++) {
	printf("          %s -> %s\n", sources[i], dests[i]);
      }
    }
  }
}
#
function _print_object_without_id(i, n)
{
  if (length(name) > 0) {
    printf("XNAMED %s %s(%s)\n", type, class, name);
  }
  else {
    printf("XUNNAMED %s %s\n", type, class);
  }

  if (length(children) > 0) {
    if (parent != id) {
      printf("  === WARNING! Parent and Node ID doesn't match ===\n");
    }

    n = split(children, child, " ");
    for (i = 1; i <= n; i++) {
      cidx = objidx_db[child[i]];
      cclass = class_db[cidx];
      cname = name_db[cidx];

      printf("    child: %s(%s)\n", cclass, cname);
    }
  }

  if (nconn > 0) {
    for (i = 0; i < nconn; i++) {
      sn = split(sources[i], src, "@");
      dn = split(dests[i], dst, "@");
      sfield = src[1];
      sidx = objidx_db[src[2]];
      sclass = class_db[sidx];
      sname = name_db[sidx];
      dfield = dst[1];
      didx = objidx_db[dst[2]];
      dclass = class_db[didx];
      dsname = name_db[didx];

      printf("    connection: %s(%s).%s -> %s(%s).%s\n",
	     sclass, sname, sfield, dclass, dname, dfield);
    }
  }
}
#
function resolve_connector(conn)
{
  cn = split(conn, src, "@");
  cfield = src[1];
  cobjid = src[2];
  cidx = objidx_db[src[2]];
  cclass = class_db[cidx];
  cname = name_db[cidx];
}
#
function print_source_trace(source, mark)
{
  if (length(source) > 0) {
    print_source_trace(source_trace[source]);

    resolve_connector(source);
    printf("%s(%s).%s -> ", cclass, cname, cfield) |& outcmd;

    if (mark) destdone_db[source] = 1;
  }
}

function print_dest_trace(source, mark, trace, level, ndest, i)
{
  ndest = ndest_trace[source];

  if (ndest > 0) {
    dest = dest_trace[source,0];
    
    resolve_connector(dest);
    printf(" -> %s(%s).%s", cclass, cname, cfield) |& outcmd;
    trace = sprintf("%s -> %s(%s).%s", trace, cclass, cname, cfield);

    if (mark) cdone_db[dest] = 1;

    print_dest_trace(dest, mark, trace, level);
  }
  else {
    printf("\n") |& outcmd;
  }

  for (i = 1; i < ndest; i++) {
    dest = dest_trace[source,i];

    resolve_connector(dest);
    printf("%s -> %s(%s).%s", trace, cclass, cname, cfield) |& outcmd;

    if (mark) cdone_db[dest] = 1;

    print_dest_trace(dest, mark, trace, level + 1);
  }
}
#
# Print out the current node or engine info (if any)
# --------------------------------------------------
/### [0-9]+ ###/ {
  if (id >= 0) {
    db_store_object(nobj);

    if (final_print == 0) {
      db_print_object(nobj);
    }

    nobj++;
  }

  id = $2;
  class = "";
  name = "";
  type = "";
  nconn = 0;
  children = "";
}
#
# Pick up node or engine info (single line)
# -----------------------------------------
/ *(node|engine)[ \t]+DEF +[A-Za-z0-9_]+ +[A-Za-z0-9_]+ +{/ {
  type = $1;
  name = $3;
  class = $4;
}
/ *(node|engine)[ \t]+[A-Za-z0-9_]+ +{/ {
  type = $1;
  name = "";
  class = $2;
}
#
# Pick up node or engine info (multiline)
# ---------------------------------------
/^ *(node|engine)[ \t]*$/ {
  defline = 1;
  type = $1;
}
/ *DEF +[A-Za-z0-9_]+ +[A-Za-z0-9_]+ +{/ {
  if (defline > 0) {
    name = $2;
    class = $3;
    defline = 0;
  }
}
/ *[A-Za-z0-9_]+ +{/ {
  if (defline > 0) {
    name = "";
    class = $1;
    defline = 0;
  }
}
#
# Pick up connections
# -------------------
/#connect.*/ {
  dest = $2;
  source = $3;

  gsub("\"", "", dest);
  gsub("\"", "", source);

  dests[nconn] = dest;
  sources[nconn] = source;
  nconn++;

  source_trace[dest] = source;
  n = int(ndest_trace[source]);
  dest_trace[source,n] = dest;
  ndest_trace[source] = n + 1;
}
#
# Pick up list of children
# ------------------------
/#addChild.*/ {
  parent = $2;
  children = $3;

  gsub("\"", "", parent);
  gsub("\"", "", children);
}
{
  next;
}
