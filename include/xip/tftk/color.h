// -*- Mode: c++; c-indentation-style: stroustrup; c-basic-offset: 4 -*-

/*
  color.hh - Color templates header file

  Copyright (C) 2004-2005 Patric Ljung
 
  This file is part of the Patrics Common Library (PCL). PCL is part
  of the Extensible Graphics System (XGFX).

  PCL is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.
 
  PCL is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
  USA

  The authors of this software:

    Patric Ljung, plg@itn.liu.se

*/

#ifndef _color_hh_
#define _color_hh_

#include <math.h>
#include <stdlib.h>
#include "BasicOps.h"


#ifdef HAVE_NO_MATHTRUNC
inline double trunc(double t) { return int(t); }
#endif






template <class _comp_t>
class color_rgb_t {
public:
    typedef _comp_t comp_t;

    inline color_rgb_t() { }

    inline color_rgb_t(comp_t r, comp_t g, comp_t b) {
	_rgb[0] = r;
	_rgb[1] = g;
	_rgb[2] = b;
    }

    inline comp_t R() const { return _rgb[0]; }
    inline comp_t G() const { return _rgb[1]; }
    inline comp_t B() const { return _rgb[2]; }

    inline comp_t r() const { return _rgb[0]; }
    inline comp_t g() const { return _rgb[1]; }
    inline comp_t b() const { return _rgb[2]; }

    inline void R(comp_t c) { _rgb[0] = c; }
    inline void G(comp_t c) { _rgb[1] = c; }
    inline void B(comp_t c) { _rgb[2] = c; }

    inline void r(comp_t c) { _rgb[0] = c; }
    inline void g(comp_t c) { _rgb[1] = c; }
    inline void b(comp_t c) { _rgb[2] = c; }

    inline comp_t & operator [] (int i) { return _rgb[i]; }

    inline void set(comp_t r, comp_t g, comp_t b)
    {
	_rgb[0] = r;
	_rgb[1] = g;
	_rgb[2] = b;
    }

protected:
    comp_t	_rgb[3];
};

template <class _comp_t>
class color_rgba_t {
public:
    typedef _comp_t comp_t;

    inline color_rgba_t() { }

    inline color_rgba_t(comp_t r, comp_t g, comp_t b, comp_t a) {
	_rgba[0] = r;
	_rgba[1] = g;
	_rgba[2] = b;
	_rgba[3] = a;
    }

    inline comp_t R() const { return _rgba[0]; }
    inline comp_t G() const { return _rgba[1]; }
    inline comp_t B() const { return _rgba[2]; }
    inline comp_t A() const { return _rgba[3]; }

    inline comp_t r() const { return _rgba[0]; }
    inline comp_t g() const { return _rgba[1]; }
    inline comp_t b() const { return _rgba[2]; }
    inline comp_t a() const { return _rgba[3]; }

    inline void R(comp_t c) { _rgba[0] = c; }
    inline void G(comp_t c) { _rgba[1] = c; }
    inline void B(comp_t c) { _rgba[2] = c; }
    inline void A(comp_t c) { _rgba[3] = c; }

    inline void r(comp_t c) { _rgba[0] = c; }
    inline void g(comp_t c) { _rgba[1] = c; }
    inline void b(comp_t c) { _rgba[2] = c; }
    inline void a(comp_t c) { _rgba[3] = c; }

    inline comp_t & operator [] (int i) { return _rgba[i]; }

    inline void set(comp_t r, comp_t g, comp_t b, comp_t a)
    {
	_rgba[0] = r;
	_rgba[1] = g;
	_rgba[2] = b;
	_rgba[3] = a;
    }

protected:
    comp_t	_rgba[4];
};


template <class _comp_t>
class color_YpCbCr601_t {
public:
    typedef _comp_t comp_t;

    inline color_YpCbCr601_t() { }

    inline color_YpCbCr601_t(comp_t Y, comp_t Cb, comp_t Cr) {
	_ycbcr[0] = Y;
	_ycbcr[1] = Cb;
	_ycbcr[2] = Cr;
    }

    inline comp_t Y() const { return _ycbcr[0]; }
    inline comp_t Cb() const { return _ycbcr[1]; }
    inline comp_t Cr() const { return _ycbcr[2]; }

    inline void Y(comp_t c) { _ycbcr[0] = c; }
    inline void Cb(comp_t c) { _ycbcr[1] = c; }
    inline void Cr(comp_t c) { _ycbcr[2] = c; }

    inline comp_t & operator [] (int i) { return _ycbcr[i]; }

protected:
    comp_t	_ycbcr[3];
};

template <class _comp_t>
class color_cieluv_t {
public:
    typedef _comp_t comp_t;

    inline color_cieluv_t() { }

    inline color_cieluv_t(comp_t L, comp_t u, comp_t v) {
	_luv[0] = L;
	_luv[1] = u;
	_luv[2] = v;
    }

    inline comp_t L() const { return _luv[0]; }
    inline comp_t u() const { return _luv[1]; }
    inline comp_t v() const { return _luv[2]; }

    inline void L(comp_t c) { _luv[0] = c; }
    inline void u(comp_t c) { _luv[1] = c; }
    inline void v(comp_t c) { _luv[2] = c; }

    inline comp_t & operator [] (int i) { return _luv[i]; }

protected:
    comp_t	_luv[3];
};

template <class _comp_t>
class color_hsi_t {
public:
    typedef _comp_t comp_t;

    inline color_hsi_t() { }

    inline color_hsi_t(comp_t h, comp_t s, comp_t i) {
	_hsi[0] = h;
	_hsi[1] = s;
	_hsi[2] = i;
    }

    inline comp_t h() const { return _hsi[0]; }
    inline comp_t s() const { return _hsi[1]; }
    inline comp_t i() const { return _hsi[2]; }

    inline void h(comp_t c) { _hsi[0] = c; }
    inline void s(comp_t c) { _hsi[1] = c; }
    inline void i(comp_t c) { _hsi[2] = c; }

    inline comp_t & operator [] (int i) { return _hsi[i]; }

protected:
    comp_t	_hsi[3];
};

#if 0

#if 0
template <class dctp, class sctp>
inline color_YpCbCr601_t<dctp> & operator = (color_YpCbCr601_t<dctp> & dst,
					     color_hsi_t<sctp> & src)
{
    dst.Y ( 16.0 +  240.0*src.i());
    dst.Cb(128.0 + 112.0*src.s()*cos(src.h()*2*M_PI));
    dst.Cb(128.0 + 112.0*src.s()*sin(src.h()*2*M_PI));

    return dst;
}
#else
template <class dctp, class sctp>
inline void operator = (color_YpCbCr601_t<dctp> & dst,
			color_hsi_t<sctp> & src)
{
    dst.Y ( 16.0 +  240.0*src.i());
    dst.Cb(128.0 + 112.0*src.s()*cos(src.h()*2*M_PI));
    dst.Cb(128.0 + 112.0*src.s()*sin(src.h()*2*M_PI));
}
#endif

template <class dctp, class sctp>
inline color_YpCbCr601_t<dctp> & operator = (color_YpCbCr601_t<dctp> & dst,
					     color_rgb_t<sctp> & src)
{
    dst.Y ( 16.0 +  65.481*src.R() + 128.553*src.G() +  24.966*src.B());
    dst.Cb(128.0 -  37.797*src.R() -  74.203*src.G() + 112.000*src.B());
    dst.Cr(128.0 + 112.000*src.R() -  93.786*src.G() -  18.214*src.B());

    return dst;
}

#endif

//template <class dctp, class sctp>
inline color_rgb_t<float> & convert(color_rgb_t<float> & dst,
				    const color_YpCbCr601_t<int> & src)
{
    color_YpCbCr601_t<int>::comp_t Y(src.Y() - 16);
    color_YpCbCr601_t<int>::comp_t Cb(src.Cb() - 128);
    color_YpCbCr601_t<int>::comp_t Cr(src.Cr() - 128);

    dst.R(0.00456621*Y + 0.00000000*Cb + 0.00625893*Cr);
    dst.G(0.00456621*Y - 0.00153632*Cb - 0.00318811*Cr);
    dst.B(0.00456621*Y + 0.00791071*Cb + 0.00000000*Cr);

    return dst;
}

#if 0
//template <class dctp, class sctp>
inline color_cieluv_t<float> & convert(color_cieluv_t<float> & dst,
				       const color_rgba_t<float> & src)
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

    double r = src.R() * src.A();
    double g = src.G() * src.A();
    double b = src.B() * src.A();

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
#endif 

#if 0


template <class dctp, class sctp>
inline color_rgb_t<dctp> & convert(color_rgb_t<dctp> & dst,
				   color_hsi_t<sctp> & src)
{
    sctp H = src.h() * 2.0 * M_PI;	// The hue in src color is in range [0,1]

    if (H < 0.0)
	H += 2.0 * M_PI;

    if (H < (2.0 * M_PI / 3.0)) {
	dst.B(src.i()*(1.0 - src.s()));
	dst.R(src.i()*(1.0 + (src.s() * cos(H)) / (cos(M_PI / 3.0 - H))));
	dst.G(3.0 * src.i() - (dst.R() + dst.B()));
    }
    else if (H < (4.0 * M_PI / 3.0)) {
	H -= 2.0 * M_PI / 3.0;
	dst.R(src.i() * (1.0 - src.s()));
	dst.G(src.i()*(1.0 + (src.s() * cos(H)) / (cos(M_PI / 3.0 - H))));
	dst.B(3.0 * src.i() - (dst.R() + dst.G()));
    }
    else {
	H -= 4.0 * M_PI / 3.0;
	dst.G(src.i() * (1.0 - src.s()));
	dst.B(src.i()*(1.0 + (src.s() * cos(H)) / (cos(M_PI / 3.0 - H))));
	dst.R(3.0 * src.i() - (dst.G() + dst.B()));
    }

#if 0
    dctp max = dst.R() > dst.G() ? dst.R() : dst.G();
    max = max > dst.B() ? max : dst.B();

    if (max > 0) {
	dst.R(dst.R() / max);
	dst.G(dst.G() / max);
	dst.B(dst.B() / max);
    }
#endif

    return dst;
}

#endif

#if 1
template <class type_t>
inline type_t __color_max(type_t a, type_t b, type_t c)
{
    type_t max = a > b ? a : b;

    return max > c ? max : c;
}

#endif

/*
  Conversion from HSV (hexcone model) to RGB.
  Components specified in the interval 0 -- 1.

  Based on the paper by Alvy Ray Smith. Color Gamut Transform Pairs.
  SIGGRAPH '78
*/

template <class dctp, class sctp>
inline color_rgb_t<dctp> & convert(color_rgb_t<dctp> & dst,
				   color_hsi_t<sctp> & src)
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

    dst.R(r);
    dst.G(g);
    dst.B(b);

    return dst;
}

template <class dctp, class sctp>
inline color_hsi_t<dctp> & convert(color_hsi_t<dctp> & dst,
				   color_rgb_t<sctp> & src)
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



template <class _comp_t>
class color_bgr_t {
public:
    typedef _comp_t comp_t;

    inline color_bgr_t() { }

    inline color_bgr_t(comp_t r, comp_t g, comp_t b) {
	_bgr[2] = r;
	_bgr[1] = g;
	_bgr[0] = b;
    }

    inline comp_t r() const { return _bgr[2]; }
    inline comp_t g() const { return _bgr[1]; }
    inline comp_t b() const { return _bgr[0]; }

    inline void r(comp_t c) { _bgr[2] = c; }
    inline void g(comp_t c) { _bgr[1] = c; }
    inline void b(comp_t c) { _bgr[0] = c; }

    inline comp_t & operator [] (int i) { return _bgr[i]; }

protected:
    comp_t	_bgr[3];
};

template <class _comp_t>
class color_bgra_t {
public:
    typedef _comp_t comp_t;

    inline color_bgra_t() { }

    inline color_bgra_t(comp_t r, comp_t g, comp_t b, comp_t a) {
	_bgra[0] = b;
	_bgra[1] = g;
	_bgra[2] = r;
	_bgra[3] = a;
    }

    inline comp_t r() const { return _bgra[2]; }
    inline comp_t g() const { return _bgra[1]; }
    inline comp_t b() const { return _bgra[0]; }
    inline comp_t a() const { return _bgra[3]; }

    inline void r(comp_t c) { _bgra[2] = c; }
    inline void g(comp_t c) { _bgra[1] = c; }
    inline void b(comp_t c) { _bgra[0] = c; }
    inline void a(comp_t c) { _bgra[3] = c; }

    inline comp_t & operator [] (int i) { return _bgra[i]; }

protected:
    comp_t	_bgra[3];
};

/*
  Just preparing a mapper - user defined mappers can use
  boundary checking and scaling, if that is desired.

  Mapper support not yet present in color_table_t.
*/

class __default_clut_mapper_t {
public:
    int operator () (int value) const { return value; }
};



template <class _color_t>
class color_table_t {
public:
    typedef _color_t color_t;

    color_table_t()
    {
	wipeout();
    }

    color_table_t(int size)
    {
	wipeout();

	create(size);
    }

    color_table_t(color_t * table, int size, int low = 0)
    {
	wipeout();

	assign(table, size, low);
    }

    ~color_table_t()
    {
	destroy();
    }

    void assign(color_t * table, int size, int low = 0)
    {
	destroy();

	_tablebase = table;
	_table = table - low;
	_size = size;
	_private = false;
    }

    color_t * pointer() {
	return _tablebase;
    }

    const color_t & operator [] (int i) const { return _table[i]; }
    color_t & operator [] (int i) { return _table[i]; }

    int create(int size, int low = 0)
    {
	destroy();

	_tablebase = new color_t[size];

	if (!_tablebase) {
	    return -1;
	}

	_table = _tablebase - low;
	_size = size;
	_private = true;

	return 0;
    }

    void destroy()
    {
	if (_private) {
	    delete [] _tablebase;
	}

	wipeout();
    }

    template <class op_t>
    void for_all_do(op_t & op)
    {
	for (int i = 0; i < _size; i++) {
	    op(i, _tablebase[i]);
	}
    }

protected:
    void wipeout() {
	_tablebase = 0;
	_table = 0;
	_size = 0;
	_private = true;
    }

    color_t *	_tablebase;
    color_t *	_table;		// Adjusted with -low
	     
    int		_size;
    bool	_private;
};


class hsv2rgb_op_t {
public:
    hsv2rgb_op_t() { }

    template <class color_t>
    inline void operator () (color_t & c)
    {
	// Float is used as color type in transfer_lut_t
	// This is extremly hacky and ugly....
	color_hsi_t<float> * hsi = reinterpret_cast<color_hsi_t<float> *>(&c);
	color_rgb_t<float> * rgb = reinterpret_cast<color_rgb_t<float> *>(&c);

	convert(*rgb, *hsi);
    }
};


template <class col_t>
col_t & random_color_normalized(col_t & c, col_t & m, col_t & r)
{
    c[0] = m[0] + drand48()*r[0] - r[0]*0.5;
    c[1] = clamp(m[1] + drand48()*r[1] - r[1] * 0.5, 0.0, 1.0);
    c[2] = clamp(m[2] + drand48()*r[2] - r[2] * 0.5, 0.0, 1.0);

    return c;
}


#endif // _color_hh_
