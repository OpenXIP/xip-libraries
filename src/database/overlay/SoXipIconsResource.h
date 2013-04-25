/*
 *  COPYRIGHT NOTICE.  Copyright (C) 2007 Siemens Corporate Research, 
 *  Inc. ("caBIG(tm) Participant"). The eXtensible Imaging Platform
 *  (XIP) was created with NCI funding and is part of the caBIG(tm) 
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

static unsigned int xipIconWidth	= 24;
static unsigned int xipIconHeight	= 24;

/*  Call this macro repeatedly.  After each use, the pixel data can be extracted  */
#define XIP_GET_PIXEL(data,pixel) {										\
  pixel[0] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4));			\
  pixel[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2));	\
  pixel[2] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33)));		\
  data += 4;															\
}

static char *copy_rgb =
	"`Q$`>[8B<:,2<:,2<:,2<:,2<:,2<:,2<:,2<:,2<:,27W?A:*`:`Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`>[@D`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_"
	"`P\\_`P\\_`P\\_7W?A:*`:1Z\\L`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$`>[8B`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_7W?A:,(O1Z\\L+I0=`Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`>;(=`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_"
	"`P\\_`P\\_`P\\_7W?A8*H:1*@H+I0=;WCF`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$`>*T8`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\__PL\\773=773=773=777>7W?A"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`=J<1`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_"
	"`P\\__`T_[O\\SSM`2OL`\"I;7GEJ+715*T`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$`<J$*`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_>[8B<:,2<:,2<:,2<:,2<:,2<:,2<:,2"
	"<:,2<:,27W?A:*`:`Q$``Q$``Q$``Q$``Q$`<)H\"`P\\_`P\\_0:$>0:$>0:$>0:$>"
	">[@D`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_7W?A:*`:1Z\\L`Q$``Q$``Q$`"
	"`Q$`;9+Y`P\\_`P\\_`P\\__`T_^PL_\\P<_>[8B`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_"
	"`P\\_`P\\_7W?A:,(O1Z\\L+I0=`Q$``Q$``Q$`:HOQ`P\\_`P\\__0P_]`D`\\@4_Y`$_"
	">;(=`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_7W?A8*H:1*@H+I0=;WCF`Q$`"
	"`Q$`9X7J`0\\_^`L_0:$>0:$>0:$>0:$>>*T8`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_"
	"`P\\__PL\\773=773=773=777>7W?A`Q$``Q$`9'[B^PL_\\`@_Z`0_Y/\\_V?L_T/8_"
	"=J<1`P\\_`P\\_`P\\_`P\\_`P\\_`P\\_`P\\__`T_[O\\SSM`2OL`\"I;7GEJ+715*T`Q$`"
	"`Q$`8GG=\\@4`Y`,`X/\\`U_H`S?8_Q.\\`<J$*`P\\_`P\\_`P\\_`P\\_`P\\_`P\\__0P_"
	"]`L_\\@4_Z@$_X/X_U_H_S?0`15*T`Q$``Q$`8'77Y?`_W?P_0:$>0:$>0:$>0:$>"
	"<)H\"`P\\_`P\\_0:$>0:$>0:$>0:$>0:$>0:$>0:$>0:$>0:$>RO0_P>\\`15*T`Q$`"
	"`Q$`7G#2V_L_T/8_QO(`ONT`M.@_J^0`;9+Y`P\\_`P\\_`P\\__`T_^PL_\\P<_Z`0_"
	"XO`_V?L`T/<_R/(_ONT_M.D_15*T`Q$``Q$`76W/S?0_Q/$`NNL`L>@_J>(_H=\\_"
	":HOQ`P\\_`P\\__0P_]`D`\\@4_Y`$_X/X_U_H_S?8_Q/$_NNT`L>8`J>(`15*T`Q$`"
	"`Q$`76W/P>\\`N.H_K^4`I=``GMP`E]H_9X7J`0\\_^`L_0:$>0:$>0:$>0:$>0:$>"
	"0:$>0:$>0:$>0:$>I^$`GMT`15*T`Q$``Q$`76W/76W/76W/76W/76W/76W/76W/"
	"9'[B^PL_\\`@_Z`0_Y/\\_V?L_T/8_QO(_ONT`M>@_J^0`H]``F]P`E=@`15*T`Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`8GG=\\@4`Y`,`X/\\`U_H`S?8_Q.\\`N^L_"
	"L>8`J>(_H-T_F=H`D]8`C-4`15*T`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"8'77Y?`_W?P_0:$>0:$>0:$>0:$>0:$>0:$>0:$>0:$>0:$>B],`AM$`15*T`Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`7G#2V_L_T/8_QO(`ONT`M.@_J^0`H]``"
	"G-L`E-@`CM4`BM(`A<``A<``15*T`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"76W/S?0_Q/$`NNL`L>@_J>(_H=\\_FML`D]8`C=,`A]$`A<``A<``A<``15*T`Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`76W/P>\\`N.H_K^4`I=``GMP`E]H_D-8`"
	"B],`AL``A<``A<``A<``A<``15*T`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"76W/76W/76W/76W/76W/76W/76W/76W/76W/76W/76W/76W/76W/76W/15*T`Q$`"
	"";

static char *cut_rgb =
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`6W*V`Q$``Q$``Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$``Q$`6W*V6W*V`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`6W*V]`0X6W*V`Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`6W*V56NP`Q$``Q$``Q$`"
	"`Q$``Q$`6W*V^P<[Z?8O6W*V`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$``Q$``Q$`6W*VS=L96W*V`Q$``Q$``Q$``Q$`6W*VZ?8OU^0B6W*V`Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`6W*VY_0NZ?<L6W*V`Q$`"
	"`Q$``Q$`6W*VU>(BQ-$66W*V`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$``Q$``Q$`6W*V]`0X_PL\\Y/(J6W*V`Q$``Q$`6W*VQ-$6L[`*6W*V`Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`6W*V\\?XTX>XJQM46"
	"6W*V`Q$`6W*VL[`*HJ[`6W*V`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$`6W*VTM\\?Q-$6K;L%6W*V6W*VHJ[^FJ;Y6W*V`Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`6W*VM<(,"
	"I[0\"E:+U6W*VAI3EFJ;Y6W*V`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$`6W*VG*C[FJ;YC)KL6W*VA93E6W*V`Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"6W*VFJ;Y.%&56W*V6W*V%$\"Y`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`6W*V?X_?FJ;Y.5FU#3S$(EWG!SC,"
	"!SC,!SC,`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$``Q$`$S^Z.%BT#3S'!CC/)V?R\"3W1!SC,!SC,!SC,!SC,`Q$``Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`&5+@!SC,!3;,!SC,%U+A\"#K0"
	"`Q$``Q$`!SC,!SC,!SC,`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$`!SC,+V[U*6OR!SC,!SC,\"#K/!C?,`Q$``Q$``Q$`!SC,!SC,`Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`!SC,!SC,!SC,!SC,!SC,!SC,!37*!SC,"
	"`Q$``Q$``Q$`!SC,!SC,`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`!SC,"
	"!SC,!SC,`Q$`!SC,!SC,!SC,!SC,!SC,!SC,`Q$``Q$`!SC,!SC,`Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$`!SC,!SC,`Q$``Q$``Q$`!SC,!SC,`Q$`!SC,"
	"!SC,!SC,!SC,!SC,!SC,`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`!SC,"
	"!SC,`Q$``Q$``Q$`!SC,!SC,`Q$``Q$`!SC,!SC,!SC,!SC,`Q$``Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$`!SC,!SC,`Q$``Q$``Q$`!SC,!SC,`Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"!SC,!SC,!SC,!SC,!SC,!SC,`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`!SC,!SC,!SC,!SC,`Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"";

static char *paste_rgb =
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$`;6^X8W6Q8W6Q8W6Q8W6Q8W6Q8W6Q;6^X`Q$`"
	"`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`AEM!HX-IHX-IBWV\";G^Y"
	"SM\\8V.D?V.D?V.D?V.D?RMP5;'RWC'ALHWU2HWU2AEM!`Q$``Q$``Q$``Q$``Q$`"
	"`Q$``Q$`CE91XMOF`OW?QLW:8W6QJ[_][?LO`P\\_`P\\_`P\\_`P\\_XO(GI;GX8W6Q"
	"L[F[`O*KZ=*1CE91`Q$``Q$``Q$``Q$``Q$``Q$`AEM!``+[`O*K:'BPL<4\"SM\\8"
	"V.D?V.D?V.D?V.D?V.D?V.D?SM\\8J[_]:'BP`O*K`O*KAEM!`Q$``Q$``Q$``Q$`"
	"`Q$``Q$`AEM!``#R`O*KEZ/!8W6Q8W6Q8W6Q8W6Q8W6Q8W6Q8W6Q8W6Q8W6Q8W6Q"
	"J;&\\`O*J`/&IAEM!`Q$``Q$``Q$``Q$``Q$``Q$`AEM!``#R`O*K__&N[>3([>3("
	"[>3([>3([>3([>3([>3([>3([>3([N7%`/\"H_^ZE_^VEAEM!`Q$``Q$``Q$``Q$`"
	"`Q$``Q$`AEM!``#R`O*K`O*K`O*K`O*K`O*K`O*K`O*K`O*K`O*K`O*J`/\"H_^VE"
	"_NRA_.F?_.J@AEM!`Q$``Q$``Q$``Q$``Q$``Q$`AEM!``#R`O*K`O*K`O*K`O*K"
	">[8B<:,2<:,2<:,2<:,2<:,2<:,2<:,2<:,29'[K:9\\'?&A7`Q$``Q$``Q$``Q$`"
	"`Q$``Q$`AEM!``#R`O*K`O*K`O*K`O*K>[@D```_```_```_```_```_```_```_"
	"```_7W?A9)H#5J8#`A(``Q$``Q$``Q$``Q$``Q$`AEM!``#R`O*K`O*K`O*K`/&J"
	">[8B```_```_```_```_```_```_```_```_7W?A8ZH63[8P.H`D`Q$``Q$``Q$`"
	"`Q$``Q$`AEM!``#R`O*K`/&I`/\"G_^VD>;(=```_```_```_```_```_```_```_"
	"```_7W?A79@'2JTJ*YHC*YHC`Q$``Q$``Q$``Q$`AEM!`O_P_^ZG_NVD_.J@^^B="
	">*T8```_```_```_```_```_```_```_```_7W?A7W?A7W?A7W?A7G;@`Q$``Q$`"
	"`Q$``Q$`AEM!`/[L_.J@^^B=^N6:^.28=J80```_```_```_```_```_```_```_"
	"_`\\_Y/0DT.01M<?WJ;?D15*T`Q$``Q$``Q$``Q$`AEM!__OJ^N6:^.27]^&5]M^2"
	"<9`(```_```_```_```_```_```__`T_^PL_]0@_[@4_Y@$_W?X_15*T`Q$``Q$`"
	"`Q$``Q$`AEM!_OGE]^&4]M^2]-R/\\]N,;Y?````_```_0:$>0:$>0:$>0:$>0:$>"
	"0:$>0:$>0:$>V_P`T_@_15*T`Q$``Q$``Q$``Q$`AEM!_/;@]-R/\\]N,\\MF)\\=:&"
	";)#V```_```_```_`0\\__0P_]PD`[`<_Z@,`X?\\_V/L_S_<_R/(`15*T`Q$``Q$`"
	"`Q$``Q$`AEM!^_/9\\MF)\\=:&[]2#[M*!:8CM```_```__`T_^`P_]0D_[@4`YP$_"
	"WOX`U?H_SO8_Q?(_O.T_15*T`Q$``Q$``Q$``Q$`AEM!^O#2[]2#[M*![=!^Z\\U\\"
	"9H+F```__`T`0:$>0:$>0:$>0:$>0:$>0:$>0:$>0:$>NNL_L>@`15*T`Q$``Q$`"
	"`Q$``Q$`AEM!^.W+Z]!^ZLU[Z<MYY\\IV8WO?_0T_]`D_\\@<_ZP,_X?\\_V?L`T/<`"
	"R?(_P.X`N.H`K^8`J.(`15*T`Q$``Q$``Q$``Q$`AEM!]^K$Z<MXY\\IVYL=TY<5Q"
	"87;9]PD_[`<_Y`,_X/\\`U_L`S_8`QO(_ONT`M>D_KN4`I=`_GMP_15*T`Q$``Q$`"
	"`Q$``Q$`AEM!^.[1YL=SY<5QY,)NXL%L7W+3[@0_Y@$_0:$>0:$>0:$>0:$>0:$>"
	"0:$>0:$>0:$>G-P`E=@`15*T`Q$``Q$``Q$``Q$`GDUQPZJ3]_#>\\^C,\\N?*\\N7)"
	"76W/XO`_V_P_TO<`R?0_P>\\_N>H`L.@`J>(`H=\\`F]L`E-<`CM4`15*T`Q$``Q$`"
	"`Q$``Q$``Q$`GDUQAEM!AEM!AEM!AEM!76W/V?L`T/<_R/,_O^X_MND`K^4`I^$`"
	"H-T_FML`DM8`C=,`B-$`15*T`Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$``Q$`"
	"76W/76W/76W/76W/76W/76W/76W/76W/76W/76W/76W/76W/76W/15*T`Q$``Q$`"
	"";