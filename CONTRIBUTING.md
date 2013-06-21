How to Contribute
==============

We welcome community contributions to the XIP&trade; project.
Your contributions back to XIP will allow the broader
community to benefit from your work and will allow your
enhancements to be integrated with those of others.  There are a few
guidelines that we ask contributors to follow so that we can have a
chance of keeping on top of things.


Getting Started
---------------

* Make sure you have an account on one of the OpenXIP git repository mirrors, such as
   [GitHub](https://github.com/signup/free) or
   [*imp* hub](https://plans.imphub.org/secure/Signup!default.jspa).

* Fork the repository on your chosen mirror (i.e. GitHub or *imp* hub) so that you can
   publish any proposed changes.

* Optionally submit a ticket for your issue or new feature to the
  [XIP planning and tracking tool on *imp* hub](https://plans.imphub.org/browse/XIP),
  or add a comment to an existing ticket, to let the world know you are working on the issue.

  - Get an [*imp* hub Account](https://plans.imphub.org/secure/Signup!default.jspa) to create or edit an issue.
  - Search for your issue, to see if anyone else might be working on it. If not found, please create a new one.
  - Clearly describe the issue including steps to reproduce if it is a bug.
  - Make sure you fill in the earliest version that you know has the issue.
  - Include a comment indicating that you would like to work on the issue,
    referring to your fork.
  - If others are interested in the issue, please feel free to coordinate 
    with them, to spread the load and minimize duplication of effort.


Making Changes
--------------

* Create a topic branch from where you want to base your work.

  - This is usually the master branch.
  - Only target release or other branches if you are certain your fix must be on a non-master branch.
  - To quickly create a topic branch based on master:

     `git checkout -b fix/master/my_contribution master`

    Please avoid working directly on the master branch.

* Make commits of logical units.

* Please provide tests and documentation with your changes.

* Check for unnecessary whitespace with `git diff --check` before committing.

* Follow the [NCIP Good Practices for Commit Messages](https://github.com/NCIP/ncip.github.com/wiki/Good-Practices#wiki-commit-messages).
  Start with a one-line summary followed by a blank line followed by a
  detailed free-form description.


Submitting Changes
------------------

* In general, we require that the OSI-approved [Apache 2.0 License](http://opensource.org/licenses/Apache-2.0)
  be applied to code contributions.  There may be cases, however, that
  warrant the use of an alternate OSI-approved license and we will
  evaluate this situations case-by-case.

* Push your changes to a topic branch in your fork of the repository.  Make sure 
  the public can read (pull) from your repository!

* Submit a pull request to the repository in the OpenXIP organization.

* Update your [XIP planning and tracking tool](https://plans.imphub.org/browse/XIP) ticket to
  indicate that you have submitted code and are ready for it to be reviewed.

  - Include a link to the pull request in the ticket
  - It would be nice, but very optional, if you also recorded the time you spent on the issue


What Happens Next?
------------------

Members of the XIP Committers team will review your proposed changes, and possibly suggest 
changes or improvements.  They will pull accepted changes back into the master XIP repository
on [*imp*hub](https://code.imphub.org/projects/XIP), which will automatically mirror the changes onto GitHub.


How Do I Become an XIP Committer?
---------------------------------

Just ask!  We are always looking for good people who are willing to dedicate some time 
towards improving XIP&trade;.  Since a majority vote of the existing XIP committers is needed
to become a committer, you may need to prove your worth first, e.g. by contributing a few 
changes or enhancements using the above process.

Additional Resources
--------------------

For help learning Git and Github, see the [NCIP Learning Resources](https://github.com/NCIP/ncip.github.com/wiki/Learning-Resources).