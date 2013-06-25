/*
Copyright (c) 2011, Siemens Corporate Research a Division of Siemens Corporation 
All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
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
