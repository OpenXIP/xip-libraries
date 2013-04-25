#ifdef WIN32
//#include <GL/wgl.h>
#endif /* WIN32 */

#ifdef LINUX
# include <GL/glx.h>
#endif /* LINUX */

#ifdef DARWIN
# include <AGL/agl.h>
#endif /* DARWIN */
