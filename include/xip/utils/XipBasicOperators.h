/*
  ------------------------------------------------------------------------

    XipBasicOperators.h

    Copyright (C) 2008, Siemens Corporate Research

    Authors:
      Patric Ljung, patric.ljung@siemens.com

    This file is part of XIP, sponsored by NSF, and provided under the
    caBIG(tm) license.  See end of file for full license.

  ------------------------------------------------------------------------
*/

#ifndef XIP_BASIC_OPERATORS
#define XIP_BASIC_OPERATORS

#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#ifndef XIP_BASIC_OPS_NONAMESPACE
namespace XipBasicOps {

#define XIP_BASIC_OPS_NAMESPACE
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#ifdef mix
#undef mix
#endif


template <class a_t, class b_t>
inline a_t min(a_t a, b_t b)
{
    return a < b ? a : b;
}

template <class a_t, class b_t>
inline a_t max(a_t a, b_t b)
{
    return a > b ? a : b;
}


template <class mix_t, class type_t>
inline mix_t mix(type_t t, mix_t a, mix_t b)
{
    return static_cast<mix_t>((1.0 - t)*a + t*b);
}


template <class type_t, class arg_t>
inline arg_t clamp(type_t t, arg_t a, arg_t b)
{
    return static_cast<arg_t>(min(max(t, a), b));
}


template< class arg_t >
inline arg_t fract(arg_t c) 
{
    return static_cast<arg_t>(c - floor(c));
}


template <class type_t>
inline type_t step(type_t t, type_t a)
{
    return t >= a;
}

template <class real_t>
class step_op {
public:
    inline step_op(real_t a) : _a(a) { }
    inline step_op() : _a(1) { }

    inline real_t operator () (real_t t)
    {
        return step(t, _a);
    }

    inline real_t operator () (real_t t, real_t a)
    {
        return step(t, a);
    }

protected:
    real_t      _a;
};


template <class type_t>
inline type_t pulse(type_t t, type_t a, type_t b)
{
    return a <= t && t < b;
}

template <class real_t>
class pulse_op {
public:
    inline pulse_op(real_t a, real_t b) : _a(a), _b(b) { }
    inline pulse_op() : _a(0), _b(1) { }

    inline real_t operator () (real_t t)
    {
        return pulse(t, _a, _b);
    }

    inline real_t operator () (real_t t, real_t a, real_t b)
    {
        return pulse(t, a, b);
    }

protected:
    real_t      _a;
    real_t      _b;
};


// smoothstep has C1 continuity (derivatives are continuous)

template <class real_t>
inline real_t smoothstep(real_t t, real_t a, real_t b)
{
    if (t < a) return 0.0;

    if (t > b) return 1.0;

    real_t x = (t - a) / (b - a);

    return x*x*(3 - 2*x);
}

template <class real_t>
class smoothstep_op {
public:
    inline smoothstep_op(real_t a, real_t b) : _a(a), _b(b), _iba(1.0 / (b - a)) { }
    inline smoothstep_op() : _a(0), _b(1), _iba(1) { }

    inline real_t operator () (real_t t)
    {
        if (t < _a) return 0.0;

        if (t > _b) return 1.0;

        real_t x = (t - _a) * _iba;

        return x*x*(3 - 2*x);
    }

protected:
    real_t      _a;
    real_t      _b;
    real_t      _iba;   // = 1.0 / (b - a)
};



// smoothstep2 has C2 continuity (2nd derivatives are continuous)

template <class real_t>
inline real_t smoothstep2(real_t t, real_t a, real_t b)
{
    if (t < a) return 0.0;

    if (t > b) return 1.0;

    real_t x = (t - a) / (b - a);

    return x*x*x*(10 + x*(6*x - 15));
}

template <class real_t>
class smoothstep2_op {
public:
    inline smoothstep2_op(real_t a, real_t b) : _a(a), _b(b), _iba(1.0 / (b - a)) { }
    inline smoothstep2_op() : _a(0), _b(1), _iba(1) { }

    inline real_t operator () (real_t t)
    {
        if (t < _a) return 0.0;

        if (t > _b) return 1.0;

        real_t x = (t - _a) * _iba;

        return x*x*x*(10 + x*(6*x - 15));
    }

protected:
    real_t      _a;
    real_t      _b;
    real_t      _iba;   // Inverse of (b - a)
};



// linearstep has C0 continuity

template <class real_t>
inline real_t linearstep(real_t t, real_t a, real_t b)
{
    if (t < a) return 0.0;
    
    if (t > b) return 1.0;

    return (t - a) / (b - a);
}

template <class real_t>
class linearstep_op {
public:
    inline linearstep_op(real_t a, real_t b) : _a(a), _b(b), _iba(1.0 / (b - a)) { }
    inline linearstep_op() : _a(0), _b(1), _iba(1) { }

    inline real_t operator () (real_t t)
    {
        if (t < _a) return 0.0;

        if (t > _b) return 1.0;

        return (t - _a) * _iba;
    }

protected:
    real_t      _a;
    real_t      _b;
    real_t      _iba;   // Inverse of (b - a)
};


template <class real_t>
inline real_t sigmoid(real_t t, real_t c, real_t s)
{
    real_t x = (t - c) / s;

    return 1.0 / (1.0 + exp(-x));
}

template <class real_t>
class sigmoid_op {
public:
    inline sigmoid_op(real_t c, real_t s) : _c(c), _is(1.0/s) { }
    inline sigmoid_op() : _c(0), _is(1) { }

    inline real_t operator () (real_t t)
    {
	real_t x = (t - _c) * _is;

	return 1.0 / (1.0 + exp(-x));
    }

    inline real_t operator () (real_t t, real_t c, real_t s)
    {
        sigmoid(t, c, s);
    }

protected:
    real_t      _c;
    real_t      _is;
};


template <class real_t>
inline real_t falsegauss(real_t t, real_t c, real_t s)
{
    real_t x = (t - c) / s;

    return 2.0 / (1.0 + exp(x*x));
}

template <class real_t>
class falsegauss_op {
public:
    inline falsegauss_op(real_t c, real_t s) : _c(c), _is(1.0/s) { }
    inline falsegauss_op() : _c(0), _is(1) { }

    inline real_t operator () (real_t t)
    {
	real_t x = (t - _c) * _is;

	return 2.0 / (1.0 + exp(x*x));
    }

    inline real_t operator () (real_t t, real_t c, real_t s)
    {
        falsegauss(t, c, s);
    }

protected:
    real_t      _c;
    real_t      _is;
};


template <class real_t>
inline real_t gauss(real_t t, real_t c, real_t s)
{
    real_t x = (t - c);
    real_t z = 2.0*s*s;

    return exp(-x*x / z) / sqrt(z*M_PI);
}


template <class real_t>
class gauss_op {
public:
    inline gauss_op(real_t c, real_t s) : _c(c) {
        real_t z = 2.0*s*s;
        _os = 1.0 / sqrt(z*M_PI);
        _is = -1.0 / z;
    }
    inline gauss_op() : _c(0) {
        real_t z = 2.0;
        _os = 1.0 / sqrt(z*M_PI);
        _is = -1.0 / z;
    }

    inline real_t operator () (real_t t)
    {
        real_t x = (t - _c);
        return _os * exp(x*x*_is);
    }

protected:
    real_t      _c;
    real_t      _is;
    real_t      _os;
};


// This spline is hardwired as Catmul-Rom splines...

template <class real_t>
class spline_op {
public:
#if defined(IRIX64) || defined(_MSC_VER)
    // MIPSPro CC compiler can't initialize static consts in class declaration.
    // We must use the enum hack or defines (these are floats, so enum hack
    // won't work)
#  define       CR00  -0.5
#  define       CR01   1.5
#  define       CR02  -1.5
#  define       CR03   0.5
#  define       CR10   1.0
#  define       CR11  -2.5
#  define       CR12   2.0
#  define       CR13  -0.5
#  define       CR20  -0.5
#  define       CR21   0.0
#  define       CR22   0.5
#  define       CR23   0.0
#  define       CR30   0.0
#  define       CR31   1.0
#  define       CR32   0.0
#  define       CR33   0.0
#endif

    inline spline_op() { }

    // We might want to think about references instead of returning
    // a new object implicitely...
    template <class type_t>
    inline type_t operator () (real_t t, int nknots, type_t * knots) const
    {
        int span;
        int nspans = nknots - 3;

        if (nspans < 1) {
            return type_t(0);
        }

        t = clamp(t, 0.0, 1.0) * nspans;
        span = static_cast<int>(t);

        // Is this really necessary?
        if (span > nknots - 3)
            span = nknots - 3;

        t -= span;
        knots += span;

        real_t c3 = CR00*knots[0] + CR01*knots[1] + CR02*knots[2] + CR03*knots[3];
        real_t c2 = CR10*knots[0] + CR11*knots[1] + CR12*knots[2] + CR13*knots[3];
        real_t c1 = CR20*knots[0] + CR21*knots[1] + CR22*knots[2] + CR23*knots[3];
        real_t c0 = CR30*knots[0] + CR31*knots[1] + CR32*knots[2] + CR33*knots[3];

        //printf("%.3f  %.3f  %.3f  %.3f  %.3f\n", t, c3, c2, c1, c0);

        return ((c3*t + c2)*t + c1)*t + c0;
    }

protected:
#ifdef CR00
#  undef CR00
#  undef CR01
#  undef CR02
#  undef CR03
#  undef CR10
#  undef CR11
#  undef CR12
#  undef CR13
#  undef CR20
#  undef CR21
#  undef CR22
#  undef CR23
#  undef CR30
#  undef CR31
#  undef CR32
#  undef CR33
#else
    static const real_t CR00 = -0.5;
    static const real_t CR01 =  1.5;
    static const real_t CR02 = -1.5;
    static const real_t CR03 =  0.5;
    static const real_t CR10 =  1.0;
    static const real_t CR11 = -2.5;
    static const real_t CR12 =  2.0;
    static const real_t CR13 = -0.5;
    static const real_t CR20 = -0.5;
    static const real_t CR21 =  0.0;
    static const real_t CR22 =  0.5;
    static const real_t CR23 =  0.0;
    static const real_t CR30 =  0.0;
    static const real_t CR31 =  1.0;
    static const real_t CR32 =  0.0;
    static const real_t CR33 =  0.0;
#endif
};


template <class real_t>
inline real_t gammacorrect(real_t t, real_t gamma)
{
    return pow(t, 1.0 / gamma);
}

template <class real_t>
class gammacorrect_op {
public:
    inline gammacorrect_op(real_t gamma) : _igamma(1.0 / gamma) { }

    inline real_t operator () (real_t t)
    {
        return pow(t, _igamma);
    }

protected:
    real_t      _igamma;
};


template <class real_t>
inline real_t bias(real_t t, real_t b)
{
    return pow(t, (real_t)(log(b) / log(0.5)));
}


template <class real_t>
class bias_op {
public:
    inline bias_op(real_t b)
    {
        _logb = log(b) / log(0.5);
    }
    inline bias_op()
    {
        _logb = 1.0;
    }

    inline real_t operator () (real_t t)
    {
        return pow(t, _logb);
    }

protected:
    real_t      _logb;
};


template <class real_t>
inline real_t gain(real_t t, real_t g)
{
    if (t < 0.5)
	return 0.5 * bias<real_t>(2.0 * t, 1.0 - g);
    else
	return 1.0 - 0.5 * bias<real_t>(2.0 - 2.0 * t, 1.0 - g);
}

template <class real_t>
class gain_op {
public:
    inline gain_op(real_t g) : _bias_op(1.0 - g) { }
    inline gain_op() { }

    inline real_t operator () (real_t t)
    {
        if (t < 0.5)
            return 0.5 * _bias_op(2.0*t);
        else
            return 1.0 - 0.5 * _bias_op(2.0 - 2.0*t);
    }

protected:
    bias_op<real_t>     _bias_op;
};

#ifndef XIP_BASIC_OPS_NONAMESPACE
}
#endif

#endif // XIP_BASIC_OPERATORS



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
