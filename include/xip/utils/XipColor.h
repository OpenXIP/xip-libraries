/*
  ------------------------------------------------------------------------
   
    XipColor.h

    Copyright (c) 2008, Siemens Corporate Research, Inc.

    This software is part of XIP (eXtensible Imaging Platform) and
    funded by NCI as a part of the caBIG(tm) initiative.  See License
    at the end of this file.

    Authors:
      Patric Ljung, patric.ljung@siemens.com


    Provides a template library for basic color manipulations, color
    space conversions and color spaces.  Classes shall be maintained
    as concrete classes (no virtual functions or additional fields!).
    Thus they can be casted to/from their element types safely and
    iterated over arrays (images and volumes).

  ------------------------------------------------------------------------
*/

#ifndef XIP_COLOR
#define XIP_COLOR

#include <stdlib.h>
#include <math.h>

#ifdef _WINDOWS
inline double trunc(double t) { return int(t); }
#endif

#define XIP_DECLARE_COLOR_CLASS_3COMP(className,a,b,c)   \
    template <class comp_t>                              \
    class className {                                    \
    public:                                              \
        typedef comp_t Component;                        \
        typedef className<comp_t> Color;                 \
                                                         \
        enum CompCount {                                 \
            NumComps = 3                                 \
        };                                               \
                                                         \
        inline className() { }                                          \
                                                                        \
        inline className(Component a, Component b, Component c)         \
        {                                                               \
            mComp[0] = a;                                               \
            mComp[1] = b;                                               \
            mComp[2] = c;                                               \
        }                                                               \
                                                                        \
        inline className(Component * src)                               \
        {                                                               \
            mComp[0] = src[0];                                          \
            mComp[1] = src[1];                                          \
            mComp[2] = src[2];                                          \
        }                                                               \
                                                                        \
        inline Component a () const { return mComp[0]; }                \
        inline Component b () const { return mComp[1]; }                \
        inline Component c () const { return mComp[2]; }                \
                                                                        \
        inline void a (Component x) { mComp[0] = x; }                   \
        inline void b (Component x) { mComp[1] = x; }                   \
        inline void c (Component x) { mComp[2] = x; }                   \
                                                                        \
        inline operator Component * () { return mComp; }                \
                                                                        \
        inline Component & operator [] (int i) { return mComp[i]; }     \
                                                                        \
        inline void set(Component a, Component b, Component c)          \
        {                                                               \
            mComp[0] = a;                                               \
            mComp[1] = b;                                               \
            mComp[2] = c;                                               \
        }                                                               \
                                                                        \
        static inline Color & safeCast(Component * comps)               \
        {                                                               \
            return *reinterpret_cast<Color *>(comps);                   \
        }                                                               \
                                                                        \
        static inline const Color & safeCastConst(const Component * comps) \
        {                                                               \
            return *reinterpret_cast<const Color *>(comps);             \
        }                                                               \
                                                                        \
    protected:                                                          \
        Component	mComp[NumComps];                                \
    }


#define XIP_DECLARE_COLOR_CLASS_4COMP(className,a,b,c,d) \
    template <class comp_t>                              \
    class className {                                    \
    public:                                              \
        typedef comp_t Component;                        \
        typedef className<comp_t> Color;                 \
                                                         \
        enum CompCount {                                 \
            NumComps = 4                                 \
        };                                               \
                                                         \
        inline className() { }                                          \
                                                                        \
        inline className(Component a, Component b, Component c, Component d) \
        {                                                               \
            mComp[0] = a;                                               \
            mComp[1] = b;                                               \
            mComp[2] = c;                                               \
            mComp[3] = d;                                               \
        }                                                               \
                                                                        \
        inline className(Component * src)                               \
        {                                                               \
            mComp[0] = src[0];                                          \
            mComp[1] = src[1];                                          \
            mComp[2] = src[2];                                          \
            mComp[3] = src[3];                                          \
        }                                                               \
                                                                        \
        inline Component a() const { return mComp[0]; }                 \
        inline Component b() const { return mComp[1]; }                 \
        inline Component c() const { return mComp[2]; }                 \
        inline Component d() const { return mComp[3]; }                 \
                                                                        \
        inline void a(Component x) { mComp[0] = x; }                    \
        inline void b(Component x) { mComp[1] = x; }                    \
        inline void c(Component x) { mComp[2] = x; }                    \
        inline void d(Component x) { mComp[3] = x; }                    \
                                                                        \
        inline operator Component * () { return mComp; }                \
                                                                        \
        inline Component & operator [] (int i) { return mComp[i]; }     \
                                                                        \
        inline void set(Component a, Component b, Component c, Component d) \
        {                                                               \
            mComp[0] = a;                                               \
            mComp[1] = b;                                               \
            mComp[2] = c;                                               \
            mComp[3] = d;                                               \
        }                                                               \
                                                                        \
        static inline Color & safeCast(Component * comps)               \
        {                                                               \
            return *reinterpret_cast<Color *>(comps);                   \
        }                                                               \
                                                                        \
        static inline const Color & safeCastConst(const Component * comps) \
        {                                                               \
            return *reinterpret_cast<const Color *>(comps);             \
        }                                                               \
                                                                        \
    protected:                                                          \
        Component	mComp[NumComps];                                \
    }


/*
  ------------------------------------------------------------------------
    Declare a few Color types in different color spaces

    Color Space classes are merely used to distinguish between different
    color spaces and should not contain much logic or functionality.
    That is provided in separate functions.
  ------------------------------------------------------------------------
*/

XIP_DECLARE_COLOR_CLASS_3COMP(XipColorRGB,r,g,b);
XIP_DECLARE_COLOR_CLASS_4COMP(XipColorRGBA,r,g,b,a);
XIP_DECLARE_COLOR_CLASS_3COMP(XipColorBGR,b,g,r);
XIP_DECLARE_COLOR_CLASS_4COMP(XipColorBGRA,b,g,r,a);

XIP_DECLARE_COLOR_CLASS_3COMP(XipColorYpCbCr601,Y,Cb,Cr);
XIP_DECLARE_COLOR_CLASS_3COMP(XipColorHSI,h,s,i);

XIP_DECLARE_COLOR_CLASS_3COMP(XipColorCIELuv,L,u,v);
XIP_DECLARE_COLOR_CLASS_3COMP(XipColorCIELab,L,a,b);

/* Color Difference in CIE*76, dL, dE and dH */
XIP_DECLARE_COLOR_CLASS_3COMP(XipColorDifferenceCIE76,dL,dE,dH);

/*
  ------------------------------------------------------------------------
    Conversion methods

    Some color space conversions...
  ------------------------------------------------------------------------
*/

/*
  ------------------------------------------------------------------------
    Convert from HSI to YpCrCb601
  ------------------------------------------------------------------------
*/


template <class dctp, class sctp>
inline XipColorYpCbCr601<dctp> &
XipColorConvert(XipColorYpCbCr601<dctp> & dst,
                const XipColorHSI<sctp> & src)
{
    dst.Y ( 16.0 +  240.0*src.i());
    dst.Cb(128.0 + 112.0*src.s()*cos(src.h()*2*M_PI));
    dst.Cb(128.0 + 112.0*src.s()*sin(src.h()*2*M_PI));

    return dst;
}


/*
  ------------------------------------------------------------------------
    Convert from RGB to YpCbCr601
  ------------------------------------------------------------------------
*/

template <class dctp, class sctp>
inline XipColorYpCbCr601<dctp> &
XipColorConvert(XipColorYpCbCr601<dctp> & dst,
                const XipColorRGB<sctp> & src)
{
    dst.Y ( 16.0 +  65.481*src.r() + 128.553*src.g() +  24.966*src.b());
    dst.Cb(128.0 -  37.797*src.r() -  74.203*src.g() + 112.000*src.b());
    dst.Cr(128.0 + 112.000*src.r() -  93.786*src.g() -  18.214*src.b());

    return dst;
}


/*
  ------------------------------------------------------------------------
    Convert from YpCbCr601<int> to RGBA<float>
  ------------------------------------------------------------------------
*/

inline XipColorRGB<float> &
XipColorConvert(XipColorRGB<float> & dst,
                const XipColorYpCbCr601<int> & src)
{
    XipColorYpCbCr601<int>::Component Y(src.Y() - 16);
    XipColorYpCbCr601<int>::Component Cb(src.Cb() - 128);
    XipColorYpCbCr601<int>::Component Cr(src.Cr() - 128);

    dst.r(0.00456621*Y + 0.00000000*Cb + 0.00625893*Cr);
    dst.g(0.00456621*Y - 0.00153632*Cb - 0.00318811*Cr);
    dst.b(0.00456621*Y + 0.00791071*Cb + 0.00000000*Cr);

    return dst;
}

/*
  ------------------------------------------------------------------------
    Convert from RGBA to CIE Luv
  ------------------------------------------------------------------------
*/

inline double cbrt(double arg) {
  return pow(arg, 1.0/3);
}

inline XipColorCIELuv<float> &
XipColorConvert(XipColorCIELuv<float> & dst,
                const XipColorRGB<float> & src)
{
    static const double SRGB_2_XYZ [3][3] = {
	{ 0.412453, 0.357580, 0.180423 },
	{ 0.212671, 0.715160, 0.072169 },
	{ 0.019334, 0.119193, 0.950227 }
    };

    // Normalized tristimulis Xn, Yn, Zn and u'n, v'n
    static const double Xn = 0.950456;
    static const double Yn = 1.0;
    static const double Zn = 1.088754;
    static const double upn = 4.0 * Xn / (Xn + 15.0 * Yn + 3 * Zn);
    static const double vpn = 9.0 * Yn / (Xn + 15.0 * Yn + 3 * Zn);

    double r = src.r();
    double g = src.g();
    double b = src.b();

    double X = SRGB_2_XYZ[0][0] * r + SRGB_2_XYZ[0][1] * g + SRGB_2_XYZ[0][2] * b;
    double Y = SRGB_2_XYZ[1][0] * r + SRGB_2_XYZ[1][1] * g + SRGB_2_XYZ[1][2] * b;
    double Z = SRGB_2_XYZ[2][0] * r + SRGB_2_XYZ[2][1] * g + SRGB_2_XYZ[2][2] * b;

    double denom = X + 15.0 * Y + 3.0 * Z;

    if (denom < 0.00000000001) {
	dst.L(0.0);
	dst.u(0.0);
	dst.v(0.0);

	return dst;
    }

    double div = 1.0 / denom;

    // Y/Yn := Y, since Yn == 1.0
    double L = (Y > 0.008856) ? 116.0 * cbrt(Y) - 16.0 : 903.3 * Y;
    double up = 4.0 * X * div;
    double vp = 9.0 * Y * div;

    dst.L(L);
    dst.u(13.0 * L * (up - upn));
    dst.v(13.0 * L * (vp - vpn));

#if 0
    printf("convert(rgba -> cieluv): rgb = %5.3f, %5.3f, %5.3f,  "
	   "XYZ = %7.3f, %7.3f, %7.3f,  "
	   "L*uv = %7.3f, %7.3f, %7.3f\n",
	   r, g, b, X, Y, Z, dst.L(), dst.u(), dst.v());
#endif

    return dst;
}

inline XipColorCIELuv<float> &
XipColorConvert(XipColorCIELuv<float> & dst,
                const XipColorRGBA<float> & src)
{
    static const double SRGB_2_XYZ [3][3] = {
	{ 0.412453, 0.357580, 0.180423 },
	{ 0.212671, 0.715160, 0.072169 },
	{ 0.019334, 0.119193, 0.950227 }
    };

    // Normalized tristimulis Xn, Yn, Zn and u'n, v'n
    static const double Xn = 0.950456;
    static const double Yn = 1.0;
    static const double Zn = 1.088754;
    static const double upn = 4.0 * Xn / (Xn + 15.0 * Yn + 3 * Zn);
    static const double vpn = 9.0 * Yn / (Xn + 15.0 * Yn + 3 * Zn);

    double r = src.r() * src.a();
    double g = src.g() * src.a();
    double b = src.b() * src.a();

    double X = SRGB_2_XYZ[0][0] * r + SRGB_2_XYZ[0][1] * g + SRGB_2_XYZ[0][2] * b;
    double Y = SRGB_2_XYZ[1][0] * r + SRGB_2_XYZ[1][1] * g + SRGB_2_XYZ[1][2] * b;
    double Z = SRGB_2_XYZ[2][0] * r + SRGB_2_XYZ[2][1] * g + SRGB_2_XYZ[2][2] * b;

    double denom = X + 15.0 * Y + 3.0 * Z;

    if (denom < 0.00000000001) {
	dst.L(0.0);
	dst.u(0.0);
	dst.v(0.0);

	return dst;
    }

    double div = 1.0 / denom;

    // Y/Yn := Y, since Yn == 1.0
    double L = (Y > 0.008856) ? 116.0 * cbrt(Y) - 16.0 : 903.3 * Y;
    double up = 4.0 * X * div;
    double vp = 9.0 * Y * div;

    dst.L(L);
    dst.u(13.0 * L * (up - upn));
    dst.v(13.0 * L * (vp - vpn));

#if 0
    printf("convert(rgba -> cieluv): rgb = %5.3f, %5.3f, %5.3f,  "
	   "XYZ = %7.3f, %7.3f, %7.3f,  "
	   "L*uv = %7.3f, %7.3f, %7.3f\n",
	   r, g, b, X, Y, Z, dst.L(), dst.u(), dst.v());
#endif

    return dst;
}


/*
  Conversion from HSV (hexcone model) to RGB.
  Components specified in the interval 0 -- 1.

  Based on the paper by Alvy Ray Smith. Color Gamut Transform Pairs.
  SIGGRAPH '78
*/

/*
  ------------------------------------------------------------------------
    Convertion from HSI to RGB
  ------------------------------------------------------------------------
*/
template <class dctp, class sctp>
inline XipColorRGB<dctp> &
XipColorConvert(XipColorRGB<dctp> & dst,
                XipColorHSI<sctp> & src)
{
    dctp h = 6*src.h();
    dctp i = trunc(h-0.000001);
    dctp f = h - i;
    dctp m = src.i() * (1 - src.s());
    dctp n = src.i() * (1 - src.s() * f);
    dctp k = src.i() * (1 - (src.s() * (1 - f)));

    dctp r, g, b;

    switch (static_cast<int>(i)) {
    case 0:
    default:
	r = src.i();
	g = k;
	b = m;
	break;
    case 1:
	r = n;
	g = src.i();
	b = m;
	break;
    case 2:
	r = m;
	g = src.i();
	b = k;
	break;
    case 3:
	r = m;
	g = n;
	b = src.i();
	break;
    case 4:
	r = k;
	g = m;
	b = src.i();
	break;
    case 5:
	r = src.i();
	g = m;
	b = n;
	break;
    }

    dst.r(r);
    dst.g(g);
    dst.b(b);

    return dst;
}

/*
  ------------------------------------------------------------------------
    Convertion from RGB to HSI
  ------------------------------------------------------------------------
*/

template <class dctp, class sctp>
inline XipColorHSI<dctp> &
XipColorConvert(XipColorHSI<dctp> & dst,
                XipColorRGB<sctp> & src)
{
    dctp v = max(max(src.r(), src.g()), src.b());
    dctp x = min(min(src.r(), src.g()), src.b());
    dctp dvx = v - x;
    dctp s;
    dctp h;

    if (dvx < 0.0000001) {
	s = 0;
	h = 0;
    }
    else {
	dctp idvx = 1.0 / dvx;
	s = dvx / v;
	dctp r = (v - src.r()) * idvx;
	dctp g = (v - src.g()) * idvx;
	dctp b = (v - src.b()) * idvx;

	if (v - src.r() < 0.0000001)
	    h = (src.g() - x < 0.0000001 ? 5 + b : 1 - g) / 6;
	else if (v - src.g() < 0.0000001)
	    h = (src.b() - x < 0.0000001 ? 1 + r : 3 - b) / 6;
	else
	    h = (src.r() - x < 0.0000001? 3 + g : 5 - r) / 6;
    }

    dst.h(h);
    dst.s(s);
    dst.i(v);

    return dst;
}



class XipColorHSI2XipColorRGBOperator {
public:
    XipColorHSI2XipColorRGBOperator() { }

    template <class color_t>
    inline void operator () (color_t & c)
    {
	// Float is used as color type in transfer_lut_t
	// This is extremly hacky and ugly....
	XipColorHSI<float> & hsi = *reinterpret_cast<XipColorHSI<float> *>(&c);
	XipColorRGB<float> & rgb = *reinterpret_cast<XipColorRGB<float> *>(&c);

	XipColorConvert(rgb, hsi);
    }
};


template <class dctp, class sctp>
static inline XipColorDifferenceCIE76<dctp> &
XipColorDifference(XipColorDifferenceCIE76<dctp> & diff,
                   const XipColorCIELuv<sctp> & src1,
                   const XipColorCIELuv<sctp> & src2)
{
    dctp dL = src1.L() - src2.L();
    dctp du = src1.u() - src2.u();
    dctp dv = src1.v() - src2.v();
    dctp dL2 = dL*dL;
    dctp duv2 = du*du + dv*dv;

    dctp dE = dL2 + duv2;

    dctp C1 = sqrt(src1.u()*src1.u() + src1.v()*src1.v());
    dctp C2 = sqrt(src2.u()*src2.u() + src2.v()*src2.v());
    dctp dC = C1 - C2;
    dctp dC2 = dC*dC;

    diff.dL(sqrt(dL2));
    diff.dE(sqrt(dE));
    diff.dH(duv2 > dC2 ? sqrt(duv2 - dC2) : 0.0);

    return diff;
}

class XipColorDifferenceOperator
{
public:
    XipColorDifferenceOperator() { }

    template <class diffColor, class srcColor>
    inline void operator () (diffColor & out,
                             srcColor & src1, srcColor & src2)
    {
        XipColorDifference(out, src1, src2);
    }
};


class XipColorDifferenceRGBtoCIE76
{
public:
    XipColorDifferenceRGBtoCIE76() { }

    template <class dctp, class sctp>
    inline void operator () (dctp & dst, sctp & s1, sctp & s2)
    {
        XipColorRGB<sctp> & c1(*reinterpret_cast<XipColorRGB<sctp> *>(&s1));
        XipColorRGB<sctp> & c2(*reinterpret_cast<XipColorRGB<sctp> *>(&s2));

        XipColorCIELuv<int> cie1, cie2;

        XipColorConvert(cie1, c1);
        XipColorConvert(cie2, c2);

        XipColorDifferenceCIE76<float> diff;

        XipColorDifference(diff, cie1, cie2);

        XipColorDifferenceCIE76<dctp> &
            out(*reinterpret_cast<XipColorDifferenceCIE76<dctp> *>(&dst));

        out.dL(diff.dL());
        out.dE(diff.dE());
        out.dH(diff.dH());
    }
};

template <class col_t>
col_t & XipRandomColorNormalized(col_t & c, col_t & m, col_t & r)
{
    c[0] = m[0] + drand48()*r[0] - r[0]*0.5;
    c[1] = clamp(m[1] + drand48()*r[1] - r[1] * 0.5, 0.0, 1.0);
    c[2] = clamp(m[2] + drand48()*r[2] - r[2] * 0.5, 0.0, 1.0);

    return c;
}


#if 0

/*
  Old, "brute force", declaration of Color classes...

  Keep them for the time being...
*/

template <class comp_t>
class XipColorYpCbCr601 {
public:
    typedef comp_t Component;
    typedef XipColorYpCbCr601 Color;

    enum CompCount {
        NumComps = 4
    };

    inline XipColorYpCbCr601() { }

    inline XipColorYpCbCr601(Component Y, Component Cb, Component Cr) {
	mComp[0] = Y;
	mComp[1] = Cb;
	mComp[2] = Cr;
    }

    inline XipColorYpCbCr601(Component * comp) {
	mComp[0] = comp[0];
	mComp[1] = comp[1];
	mComp[2] = comp[2];
    }

    inline Component Y() const { return mComp[0]; }
    inline Component Cb() const { return mComp[1]; }
    inline Component Cr() const { return mComp[2]; }

    inline void Y(Component c) { mComp[0] = c; }
    inline void Cb(Component c) { mComp[1] = c; }
    inline void Cr(Component c) { mComp[2] = c; }

    inline Component & operator [] (int i) { return mComp[i]; }

    static inline Color & safeCast(Component * comps)
    {
        return *reinterpret_cast<Color *>(comps);
    }

    static inline const Color & safeCastConst(const Component * comps)
    {
        return *reinterpret_cast<const Color *>(comps);
    }

protected:
    Component	mComp[3];
};

template <class comp_t>
class XipColorCIELuv {
public:
    typedef comp_t Component;
    typedef XipColorCIELuv<comp_t> Color;

    enum CompCount {
        NumComps = 3
    };

    inline XipColorCIELuv() { }

    inline XipColorCIELuv(Component L, Component u, Component v)
    {
	mComp[0] = L;
	mComp[1] = u;
	mComp[2] = v;
    }

    inline XipColorCIELuv(Component * comp)
    {
	mComp[0] = comp[0];
	mComp[1] = comp[1];
	mComp[2] = comp[2];
    }

    inline Component L() const { return mComp[0]; }
    inline Component u() const { return mComp[1]; }
    inline Component v() const { return mComp[2]; }

    inline void L(Component c) { mComp[0] = c; }
    inline void u(Component c) { mComp[1] = c; }
    inline void v(Component c) { mComp[2] = c; }

    inline Component & operator [] (int i) { return mComp[i]; }

    static inline Color & safeCast(Component * comps)
    {
        return *reinterpret_cast<Color *>(comps);
    }

    static inline const Color & safeCastConst(const Component * comps)
    {
        return *reinterpret_cast<const Color *>(comps);
    }

protected:
    Component	mComp[NumComps];
};


template <class comp_t>
class XipColorHSI {
public:
    typedef comp_t Component;
    typedef XipColorHSI<comp_t> Color;

    enum CompCount {
        NumComps = 3
    };

    inline XipColorHSI() { }

    inline XipColorHSI(Component h, Component s, Component i) {
	mComp[0] = h;
	mComp[1] = s;
	mComp[2] = i;
    }

    inline XipColorHSI(Component * comp)
    {
	mComp[0] = comp[0];
	mComp[1] = comp[1];
	mComp[2] = comp[2];
    }

    inline Component h() const { return mComp[0]; }
    inline Component s() const { return mComp[1]; }
    inline Component i() const { return mComp[2]; }

    inline void h(Component c) { mComp[0] = c; }
    inline void s(Component c) { mComp[1] = c; }
    inline void i(Component c) { mComp[2] = c; }

    inline Component & operator [] (int i) { return mComp[i]; }

protected:
    Component	mComp[3];
};

template <class comp_t>
class XipColorBGR {
public:
    typedef comp_t Component;

    inline XipColorBGR() { }

    inline XipColorBGR(Component r, Component g, Component b) {
	mComp[2] = r;
	mComp[1] = g;
	mComp[0] = b;
    }

    inline Component r() const { return mComp[2]; }
    inline Component g() const { return mComp[1]; }
    inline Component b() const { return mComp[0]; }

    inline void r(Component c) { mComp[2] = c; }
    inline void g(Component c) { mComp[1] = c; }
    inline void b(Component c) { mComp[0] = c; }

    inline Component & operator [] (int i) { return mComp[i]; }

protected:
    Component	mComp[3];
};

template <class comp_t>
class XipColorBGRA {
public:
    typedef comp_t Component;

    inline XipColorBGRA() { }

    inline XipColorBGRA(Component r, Component g, Component b, Component a) {
	mComp[0] = b;
	mComp[1] = g;
	mComp[2] = r;
	mComp[3] = a;
    }

    inline Component r() const { return mComp[2]; }
    inline Component g() const { return mComp[1]; }
    inline Component b() const { return mComp[0]; }
    inline Component a() const { return mComp[3]; }

    inline void r(Component c) { mComp[2] = c; }
    inline void g(Component c) { mComp[1] = c; }
    inline void b(Component c) { mComp[0] = c; }
    inline void a(Component c) { mComp[3] = c; }

    inline Component & operator [] (int i) { return mComp[i]; }

protected:
    Component	mComp[3];
};

#endif


#endif // XIP_COLOR


/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2005 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). eXtensible Imaging Platform (XIP)
 *  was created with NCI funding and is part of the caBIG(tm) 
 *  initiative. The software subject to this notice and license 
 *  includes both human readable source code form and machine 
 *  readable, binary, object code form (the "caBIG(tm) Software").
 *  
 *  This caBIG(tm) Software License (the "License") is between 
 *  caBIG(tm) Participant and You.  "You (or "Your") shall mean a 
 *  person or an entity, and all other entities that control, are 
 *  controlled by, or are under common control with the entity.  
 *  "Control" for purposes of this definition means (i) the direct or 
 *  indirect power to cause the direction or management of such 
 *  entity, whether by contract or otherwise, or (ii) ownership of 
 *  fifty percent (50%) or more of the outstanding shares, or (iii) 
 *  beneficial ownership of such entity.
 *  
 *  LICENSE.  Provided that You agree to the conditions described 
 *  below, caBIG(tm) Participant grants You a non-exclusive, 
 *  worldwide, perpetual, fully-paid-up, no-charge, irrevocable, 
 *  transferable and royalty-free right and license in its rights in 
 *  the caBIG(tm) Software, including any copyright or patent rights 
 *  therein that may be infringed by the making, using, selling, 
 *  offering for sale, or importing of caBIG(tm) Software, to (i) 
 *  use, install, access, operate, execute, reproduce, copy, modify, 
 *  translate, market, publicly display, publicly perform, and 
 *  prepare derivative works of the caBIG(tm) Software; (ii) make, 
 *  have made, use, practice, sell, and offer for sale, and/or 
 *  otherwise dispose of caBIG(tm) Software (or portions thereof); 
 *  (iii) distribute and have distributed to and by third parties the 
 *  caBIG(tm) Software and any modifications and derivative works 
 *  thereof; and (iv) sublicense the foregoing rights set out in (i), 
 *  (ii) and (iii) to third parties, including the right to license 
 *  such rights to further third parties.  For sake of clarity, and 
 *  not by way of limitation, caBIG(tm) Participant shall have no 
 *  right of accounting or right of payment from You or Your 
 *  sublicensees for the rights granted under this License.  This 
 *  License is granted at no charge to You.  Your downloading, 
 *  copying, modifying, displaying, distributing or use of caBIG(tm) 
 *  Software constitutes acceptance of all of the terms and 
 *  conditions of this Agreement.  If you do not agree to such terms 
 *  and conditions, you have no right to download, copy, modify, 
 *  display, distribute or use the caBIG(tm) Software.
 *  
 *  1.	Your redistributions of the source code for the caBIG(tm) 
 *      Software must retain the above copyright notice, this list 
 *      of conditions and the disclaimer and limitation of 
 *      liability of Article 6 below.  Your redistributions in 
 *      object code form must reproduce the above copyright notice, 
 *      this list of conditions and the disclaimer of Article 6 in 
 *      the documentation and/or other materials provided with the 
 *      distribution, if any.
 *  2.	Your end-user documentation included with the 
 *      redistribution, if any, must include the following 
 *      acknowledgment: "This product includes software developed 
 *      by Siemens Corporate Research Inc."  If You do not include 
 *      such end-user documentation, You shall include this 
 *      acknowledgment in the caBIG(tm) Software itself, wherever 
 *      such third-party acknowledgments normally appear.
 *  3.	You may not use the names "Siemens Corporate Research, 
 *      Inc.", "The National Cancer Institute", "NCI", "Cancer 
 *      Bioinformatics Grid" or "caBIG(tm)" to endorse or promote 
 *      products derived from this caBIG(tm) Software.  This 
 *      License does not authorize You to use any trademarks, 
 *  	service marks, trade names, logos or product names of 
 *      either caBIG(tm) Participant, NCI or caBIG(tm), except as 
 *      required to comply with the terms of this License.
 *  4.	For sake of clarity, and not by way of limitation, You may 
 *      incorporate this caBIG(tm) Software into Your proprietary 
 *      programs and into any third party proprietary programs.  
 *      However, if You incorporate the caBIG(tm) Software into 
 *      third party proprietary programs, You agree that You are 
 *      solely responsible for obtaining any permission from such 
 *      third parties required to incorporate the caBIG(tm) 
 *      Software into such third party proprietary programs and for 
 *      informing Your sublicensees, including without limitation 
 *      Your end-users, of their obligation to secure any required 
 *      permissions from such third parties before incorporating 
 *      the caBIG(tm) Software into such third party proprietary 
 *      software programs.  In the event that You fail to obtain 
 *      such permissions, You agree to indemnify caBIG(tm) 
 *      Participant for any claims against caBIG(tm) Participant by 
 *      such third parties, except to the extent prohibited by law, 
 *      resulting from Your failure to obtain such permissions.
 *  5.	For sake of clarity, and not by way of limitation, You may 
 *      add Your own copyright statement to Your modifications and 
 *      to the derivative works, and You may provide additional or 
 *      different license terms and conditions in Your sublicenses 
 *      of modifications of the caBIG(tm) Software, or any 
 *      derivative works of the caBIG(tm) Software as a whole, 
 *      provided Your use, reproduction, and distribution of the 
 *      Work otherwise complies with the conditions stated in this 
 *      License.
 *  6.	THIS caBIG(tm) SOFTWARE IS PROVIDED "AS IS" AND ANY 
 *      EXPRESSED OR IMPLIED WARRANTIES (INCLUDING, BUT NOT LIMITED 
 *      TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, NON-
 *      INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE) ARE 
 *      DISCLAIMED.  IN NO EVENT SHALL SIEMENS CORPORATE RESEARCH 
 *      INC. OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT, INDIRECT, 
 *      INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 *      (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE 
 *      GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR 
 *      BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 *      LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *      OF THE USE OF THIS caBIG(tm) SOFTWARE, EVEN IF ADVISED OF 
 *      THE POSSIBILITY OF SUCH DAMAGE.
 *  
 */

// Local Variables:
//   mode: c++
//   indent-tabs-mode: nil
//   c-indentation-style: k&r
//   c-basic-offset: 4
// End:
