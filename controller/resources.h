// Copyright 2009 Emilie Gillet.
//
// Author: Emilie Gillet (emilie.o.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Resources definitions.
//
// Automatically generated with:
// make resources


#ifndef CONTROLLER_RESOURCES_H_
#define CONTROLLER_RESOURCES_H_


#include "avrlib/base.h"

#include <avr/pgmspace.h>


#include "avrlib/resources_manager.h"

namespace ambika {

typedef uint16_t ResourceId;

extern const prog_char* const string_table[];

extern const prog_uint16_t* const lookup_table_table[];

extern const prog_uint8_t* const character_table[];

extern const prog_uint8_t* const waveform_table[];

extern const prog_uint16_t lut_res_lfo_increments[] PROGMEM;
extern const prog_uint16_t lut_res_scale_just[] PROGMEM;
extern const prog_uint16_t lut_res_scale_pythagorean[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_eb[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_e[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_ea[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bhairav[] PROGMEM;
extern const prog_uint16_t lut_res_scale_gunakri[] PROGMEM;
extern const prog_uint16_t lut_res_scale_marwa[] PROGMEM;
extern const prog_uint16_t lut_res_scale_shree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_purvi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bilawal[] PROGMEM;
extern const prog_uint16_t lut_res_scale_yaman[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kafi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bhimpalasree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_darbari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_rageshree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_khamaj[] PROGMEM;
extern const prog_uint16_t lut_res_scale_mimal[] PROGMEM;
extern const prog_uint16_t lut_res_scale_parameshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_rangeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_gangeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kameshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_pa__kafi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_natbhairav[] PROGMEM;
extern const prog_uint16_t lut_res_scale_m_kauns[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bairagi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_b_todi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_chandradeep[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kaushik_todi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_jogeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_arpeggiator_patterns[] PROGMEM;
extern const prog_uint16_t lut_res_groove_swing[] PROGMEM;
extern const prog_uint16_t lut_res_groove_shuffle[] PROGMEM;
extern const prog_uint16_t lut_res_groove_push[] PROGMEM;
extern const prog_uint16_t lut_res_groove_lag[] PROGMEM;
extern const prog_uint16_t lut_res_groove_human[] PROGMEM;
extern const prog_uint16_t lut_res_groove_monkey[] PROGMEM;
extern const prog_uint8_t chr_res_special_characters[] PROGMEM;
extern const prog_uint8_t wav_res_lfo_waveforms[] PROGMEM;
#define STR_RES_WAVEFORM 0  // waveform
#define STR_RES_PARAMETER 1  // parameter
#define STR_RES_RANGE 2  // range
#define STR_RES_TUNE 3  // tune
#define STR_RES_OSC_MIX 4  // osc mix
#define STR_RES_SUB_OSC_ 5  // sub osc.
#define STR_RES_CROSSMOD_ 6  // crossmod.
#define STR_RES_OPERATOR 7  // operator
#define STR_RES_AMOUNT 8  // amount
#define STR_RES_RESONANCE 9  // resonance
#define STR_RES_MODE 10  // mode
#define STR_RES_ENV2TVCF 11  // env2~vcf
#define STR_RES_LFO2TVCF 12  // lfo2~vcf
#define STR_RES_VELOTVCF 13  // velo~vcf
#define STR_RES_KEYBTVCF 14  // keyb~vcf
#define STR_RES_CRV1 15  // crv1
#define STR_RES_CRV2 16  // crv2
#define STR_RES_CRV3 17  // crv3
#define STR_RES_ENV1_CURVE 18  // env1 curve
#define STR_RES_ENV2_CURVE 19  // env2 curve
#define STR_RES_ENV3_CURVE 20  // env3 curve
#define STR_RES_VINT 21  // vint
#define STR_RES_VINTAGE 22  // vintage
#define STR_RES_VOICE 23  // voice
#define STR_RES_STL 24  // stl
#define STR_RES_VOICE_STEAL 25  // voice steal
#define STR_RES_SLEW 26  // slew
#define STR_RES_VELO_CURVE 27  // velo curve
#define STR_RES_OSCILLATOR_1 28  // oscillator 1
#define STR_RES_OSCILLATOR_2 29  // oscillator 2
#define STR_RES_MIXER 30  // mixer
#define STR_RES_LFO 31  // lfo
#define STR_RES_FILTER_1 32  // filter 1
#define STR_RES_FILTER_2 33  // filter 2
#define STR_RES_ENVELOPE 34  // envelope
#define STR_RES_CLOCK 35  // clock
#define STR_RES_SYSTEM 36  // system
#define STR_RES_CRUSH 37  // crush
#define STR_RES_FREQUENCY 38  // frequency
#define STR_RES_ARPEGGIO 39  // arpeggio
#define STR_RES_SEQUENCER 40  // sequencer
#define STR_RES_SPRM 41  // sprm
#define STR_RES_SPREAD_MODE 42  // spread mode
#define STR_RES_STCK 43  // stck
#define STR_RES_CNTR 44  // cntr
#define STR_RES_WIDE 45  // wide
#define STR_RES_SUB 46  // sub-
#define STR_RES_ATTACK 47  // attack
#define STR_RES_DECAY 48  // decay
#define STR_RES_SUSTAIN 49  // sustain
#define STR_RES_RELEASE 50  // release
#define STR_RES_TRIGGER 51  // trigger
#define STR_RES_RATE 52  // rate
#define STR_RES_LFO_EG 53  // lfo/eg
#define STR_RES_VOICE_LFO 54  // voice lfo
#define STR_RES_SOURCE 55  // source
#define STR_RES_DESTINATION 56  // destination
#define STR_RES_IN1 57  // in1
#define STR_RES_IN2 58  // in2
#define STR_RES_MODULATION 59  // modulation
#define STR_RES_MODUL_ 60  // modul.
#define STR_RES__MODULATION 61  // modulation
#define STR_RES_MODIFIER 62  // modifier
#define STR_RES_MODIF_ 63  // modif.
#define STR_RES_VOLUME 64  // volume
#define STR_RES_OCTAVE 65  // octave
#define STR_RES_SPREAD 66  // spread
#define STR_RES_LEGATO 67  // legato
#define STR_RES_PORTAMENTO 68  // portamento
#define STR_RES_ARP_SEQ 69  // arp/seq
#define STR_RES_RAGA 70  // raga
#define STR_RES_DIRECTION 71  // direction
#define STR_RES_PATTERN 72  // pattern
#define STR_RES_CHANNEL 73  // channel
#define STR_RES_PART 74  // part
#define STR_RES_BPM 75  // bpm
#define STR_RES_LTCH 76  // ltch
#define STR_RES_LATCH 77  // latch
#define STR_RES_LOW 78  // low
#define STR_RES_HIGH 79  // high
#define STR_RES_GRID 80  // grid
#define STR_RES_SEQ1_LEN 81  // seq1 len
#define STR_RES_SEQ2_LEN 82  // seq2 len
#define STR_RES_PATT_LEN 83  // patt len
#define STR_RES_LEN1 84  // len1
#define STR_RES_LEN2 85  // len2
#define STR_RES_LENP 86  // lenp
#define STR_RES_GROOVE 87  // groove
#define STR_RES_MIDI 88  // midi
#define STR_RES_SNAP 89  // snap
#define STR_RES_HELP 90  // help
#define STR_RES_AUTO_BACKUP 91  // auto backup
#define STR_RES_LEDS 92  // leds
#define STR_RES_CARD_LEDS 93  // card leds
#define STR_RES_SWAP_COLORS 94  // swap colors
#define STR_RES_INPT_FILTER 95  // inpt filter
#define STR_RES_OUTP_MODE 96  // outp mode
#define STR_RES_EXT 97  // ext
#define STR_RES_OMNI 98  // omni
#define STR_RES_AMNT 99  // amnt
#define STR_RES_SRCE 100  // srce
#define STR_RES_OCT 101  // oct
#define STR_RES_SPRD 102  // sprd
#define STR_RES_A_SQ 103  // a/sq
#define STR_RES_OCTV 104  // octv
#define STR_RES_OFF 105  // off
#define STR_RES_ON 106  // on
#define STR_RES_NONE 107  // none
#define STR_RES_SAW 108  // saw
#define STR_RES_SQUARE 109  // square
#define STR_RES_TRIANGLE 110  // triangle
#define STR_RES_SINE 111  // sine
#define STR_RES_ZSAW 112  // zsaw
#define STR_RES_LPZSAW 113  // lpzsaw
#define STR_RES_PKZSAW 114  // pkzsaw
#define STR_RES_BPZSAW 115  // bpzsaw
#define STR_RES_HPZSAW 116  // hpzsaw
#define STR_RES_LPZPULSE 117  // lpzpulse
#define STR_RES_PKZPULSE 118  // pkzpulse
#define STR_RES_BPZPULSE 119  // bpzpulse
#define STR_RES_HPZPULSE 120  // hpzpulse
#define STR_RES_ZTRIANGLE 121  // ztriangle
#define STR_RES_PAD 122  // pad
#define STR_RES_FM 123  // fm
#define STR_RES_8BITS 124  // 8bits
#define STR_RES_PWM 125  // pwm
#define STR_RES_NOISE 126  // noise
#define STR_RES_VOWEL 127  // vowel
#define STR_RES_MALE 128  // male
#define STR_RES_FEMALE 129  // female
#define STR_RES_CHOIR 130  // choir
#define STR_RES_TAMPURA 131  // tampura
#define STR_RES_BOWED 132  // bowed
#define STR_RES_CELLO 133  // cello
#define STR_RES_VIBES 134  // vibes
#define STR_RES_SLAP 135  // slap
#define STR_RES_EPIANO 136  // epiano
#define STR_RES_ORGAN 137  // organ
#define STR_RES_WAVES 138  // waves
#define STR_RES_DIGITAL 139  // digital
#define STR_RES_DRONE_1 140  // drone 1
#define STR_RES_DRONE_2 141  // drone 2
#define STR_RES_METALLIC 142  // metallic
#define STR_RES_BELL 143  // bell
#define STR_RES_WAVQUENCE 144  // wavquence
#define STR_RES_OLDSAW 145  // oldsaw
#define STR_RES_QPWM 146  // qpwm
#define STR_RES_FMFB 147  // fmfb
#define STR_RES_CSAW 148  // csaw
#define STR_RES_VOWEL_2 149  // vowel 2
#define STR_RES_TRI 150  // tri
#define STR_RES_SQR 151  // sqr
#define STR_RES_S_H 152  // s&h
#define STR_RES_RAMP 153  // ramp
#define STR_RES__SINE 154  // sine
#define STR_RES_HRM2 155  // hrm2
#define STR_RES_HRM3 156  // hrm3
#define STR_RES_HRM5 157  // hrm5
#define STR_RES_GRG1 158  // grg1
#define STR_RES_GRG2 159  // grg2
#define STR_RES_BAT1 160  // bat1
#define STR_RES_BAT2 161  // bat2
#define STR_RES_SPK1 162  // spk1
#define STR_RES_SPK2 163  // spk2
#define STR_RES_LSAW 164  // lsaw
#define STR_RES_LSQR 165  // lsqr
#define STR_RES_RSAW 166  // rsaw
#define STR_RES_RSQR 167  // rsqr
#define STR_RES_STP1 168  // stp1
#define STR_RES_STP2 169  // stp2
#define STR_RES___OFF 170  // off
#define STR_RES_SYNC 171  // sync
#define STR_RES_RINGMOD 172  // ringmod
#define STR_RES_XOR 173  // xor
#define STR_RES_FOLD 174  // fold
#define STR_RES_BITS 175  // bits
#define STR_RES_SQU1 176  // squ1
#define STR_RES_TRI1 177  // tri1
#define STR_RES_PUL1 178  // pul1
#define STR_RES_SQU2 179  // squ2
#define STR_RES_TRI2 180  // tri2
#define STR_RES_PUL2 181  // pul2
#define STR_RES_CLICK 182  // click
#define STR_RES_GLITCH 183  // glitch
#define STR_RES_BLOW 184  // blow
#define STR_RES_METAL 185  // metal
#define STR_RES_POP 186  // pop
#define STR_RES_ENV1 187  // env1
#define STR_RES_ENV2 188  // env2
#define STR_RES_ENV3 189  // env3
#define STR_RES_LFO1 190  // lfo1
#define STR_RES_LFO2 191  // lfo2
#define STR_RES_LFO3 192  // lfo3
#define STR_RES_LFO4 193  // lfo4
#define STR_RES_MOD1 194  // mod1
#define STR_RES_MOD2 195  // mod2
#define STR_RES_MOD3 196  // mod3
#define STR_RES_MOD4 197  // mod4
#define STR_RES_SEQ1 198  // seq1
#define STR_RES_SEQ2 199  // seq2
#define STR_RES_ARP 200  // arp
#define STR_RES_VELO 201  // velo
#define STR_RES_AFTR 202  // aftr
#define STR_RES_BEND 203  // bend
#define STR_RES_MWHL 204  // mwhl
#define STR_RES_WHL2 205  // whl2
#define STR_RES_PDAL 206  // pdal
#define STR_RES_NOTE 207  // note
#define STR_RES_GATE 208  // gate
#define STR_RES_NOIS 209  // nois
#define STR_RES_RAND 210  // rand
#define STR_RES_E256 211  // =256
#define STR_RES_E128 212  // =128
#define STR_RES_E64 213  // =64
#define STR_RES_E32 214  // =32
#define STR_RES_E16 215  // =16
#define STR_RES_E8 216  // =8
#define STR_RES_E4 217  // =4
#define STR_RES_PRM1 218  // prm1
#define STR_RES_PRM2 219  // prm2
#define STR_RES_OSC1 220  // osc1
#define STR_RES_OSC2 221  // osc2
#define STR_RES_31S2 222  // 1+2
#define STR_RES_VIBR 223  // vibr
#define STR_RES_MIX 224  // mix
#define STR_RES_XMOD 225  // xmod
#define STR_RES__NOIS 226  // nois
#define STR_RES__SUB 227  // sub
#define STR_RES_FUZZ 228  // fuzz
#define STR_RES_CRSH 229  // crsh
#define STR_RES_FREQ 230  // freq
#define STR_RES_RESO 231  // reso
#define STR_RES_ATTK 232  // attk
#define STR_RES_DECA 233  // deca
#define STR_RES_RELE 234  // rele
#define STR_RES__LFO4 235  // lfo4
#define STR_RES_VCA 236  // vca
#define STR_RES_ENV_1 237  // env 1
#define STR_RES_ENV_2 238  // env 2
#define STR_RES_ENV_3 239  // env 3
#define STR_RES_LFO_1 240  // lfo 1
#define STR_RES_LFO_2 241  // lfo 2
#define STR_RES_LFO_3 242  // lfo 3
#define STR_RES_LFO_4 243  // lfo 4
#define STR_RES_MOD__1 244  // mod. 1
#define STR_RES_MOD__2 245  // mod. 2
#define STR_RES_MOD__3 246  // mod. 3
#define STR_RES_MOD__4 247  // mod. 4
#define STR_RES_SEQ__1 248  // seq. 1
#define STR_RES_SEQ__2 249  // seq. 2
#define STR_RES__ARP 250  // arp
#define STR_RES__VELO 251  // velo
#define STR_RES_AFTTCH 252  // afttch
#define STR_RES_BENDER 253  // bender
#define STR_RES_MWHEEL 254  // mwheel
#define STR_RES_WHEEL2 255  // wheel2
#define STR_RES_PEDAL 256  // pedal
#define STR_RES__NOTE 257  // note
#define STR_RES__GATE 258  // gate
#define STR_RES__NOISE 259  // noise
#define STR_RES_RANDOM 260  // random
#define STR_RES_E_256 261  // = 256
#define STR_RES_E_32 262  // = 32
#define STR_RES_E_16 263  // = 16
#define STR_RES_E_8 264  // = 8
#define STR_RES_E_4 265  // = 4
#define STR_RES_PARAM_1 266  // param 1
#define STR_RES_PARAM_2 267  // param 2
#define STR_RES_OSC_1 268  // osc 1
#define STR_RES_OSC_2 269  // osc 2
#define STR_RES_OSC_1S2 270  // osc 1+2
#define STR_RES_VIBRATO 271  // vibrato
#define STR_RES__MIX 272  // mix
#define STR_RES__XMOD 273  // xmod
#define STR_RES___NOISE 274  // noise
#define STR_RES_SUBOSC 275  // subosc
#define STR_RES__FUZZ 276  // fuzz
#define STR_RES__CRUSH 277  // crush
#define STR_RES__FREQUENCY 278  // frequency
#define STR_RES__RESO 279  // reso
#define STR_RES__ATTACK 280  // attack
#define STR_RES__DECAY 281  // decay
#define STR_RES__RELEASE 282  // release
#define STR_RES__LFO_4 283  // lfo 4
#define STR_RES__VCA 284  // vca
#define STR_RES_LP 285  // lp
#define STR_RES_BP 286  // bp
#define STR_RES_HP 287  // hp
#define STR_RES_NT 288  // nt
#define STR_RES_FREE 289  // free
#define STR_RES_ENVTLFO 290  // env~lfo
#define STR_RES_LFOTENV 291  // lfo~env
#define STR_RES_STEP_SEQ 292  // step seq
#define STR_RES__ARPEGGIO 293  // arpeggio
#define STR_RES__PATTERN 294  // pattern
#define STR_RES__OFF 295  // off
#define STR_RES_ADD 296  // add
#define STR_RES_PROD 297  // prod
#define STR_RES_ATTN 298  // attn
#define STR_RES_MAX 299  // max
#define STR_RES_MIN 300  // min
#define STR_RES__XOR 301  // xor
#define STR_RES_GE 302  // >=
#define STR_RES_LE 303  // <=
#define STR_RES_QTZ 304  // qtz
#define STR_RES_LAG 305  // lag
#define STR_RES_MONO 306  // mono
#define STR_RES_POLY 307  // poly
#define STR_RES_2X_UNISON 308  // 2x unison
#define STR_RES_CYCLIC 309  // cyclic
#define STR_RES_CHAIN 310  // chain
#define STR_RES_3X_UNISON 311  // 3x unison
#define STR_RES_4X_UNISON 312  // 4x unison
#define STR_RES_OLD 313  // old
#define STR_RES__LOW 314  // low
#define STR_RES__HIGH 315  // high
#define STR_RES__NONE 316  // none
#define STR_RES__FREE 317  // free
#define STR_RES__ENVTLFO 318  // env~lfo
#define STR_RES_ONCE 319  // once
#define STR_RES_LIN 320  // lin
#define STR_RES_SOFT 321  // soft
#define STR_RES_HARD 322  // hard
#define STR_RES_UP 323  // up
#define STR_RES_DOWN 324  // down
#define STR_RES_UP_DOWN 325  // up&down
#define STR_RES_PLAYED 326  // played
#define STR_RES__RANDOM 327  // random
#define STR_RES_CHORD 328  // chord
#define STR_RES_1_1 329  // 1/1
#define STR_RES_3_4 330  // 3/4
#define STR_RES_2_3 331  // 2/3
#define STR_RES_1_2 332  // 1/2
#define STR_RES_3_8 333  // 3/8
#define STR_RES_1_3 334  // 1/3
#define STR_RES_1_4 335  // 1/4
#define STR_RES_1_6 336  // 1/6
#define STR_RES_1_8 337  // 1/8
#define STR_RES_1_12 338  // 1/12
#define STR_RES_1_16 339  // 1/16
#define STR_RES_1_24 340  // 1/24
#define STR_RES_1_32 341  // 1/32
#define STR_RES_1_48 342  // 1/48
#define STR_RES_1_96 343  // 1/96
#define STR_RES_THRU 344  // thru
#define STR_RES__SEQUENCER 345  // sequencer
#define STR_RES_CONTROLLR 346  // controllr
#define STR_RES__CHAIN 347  // chain
#define STR_RES_FULL 348  // full
#define STR_RES_____ 349  // ....
#define STR_RES____S 350  // ...s
#define STR_RES___P_ 351  // ..p.
#define STR_RES___PS 352  // ..ps
#define STR_RES__N__ 353  // .n..
#define STR_RES__N_S 354  // .n.s
#define STR_RES__NP_ 355  // .np.
#define STR_RES__NPS 356  // .nps
#define STR_RES_C___ 357  // c...
#define STR_RES_C__S 358  // c..s
#define STR_RES_C_P_ 359  // c.p.
#define STR_RES_C_PS 360  // c.ps
#define STR_RES_CN__ 361  // cn..
#define STR_RES_CN_S 362  // cn.s
#define STR_RES_CNP_ 363  // cnp.
#define STR_RES_CNPS 364  // cnps
#define STR_RES_SWING 365  // swing
#define STR_RES_SHUFFLE 366  // shuffle
#define STR_RES_PUSH 367  // push
#define STR_RES__LAG 368  // lag
#define STR_RES_HUMAN 369  // human
#define STR_RES_MONKEY 370  // monkey
#define STR_RES__OSCILLATOR_1 371  // oscillator 1
#define STR_RES__OSCILLATOR_2 372  // oscillator 2
#define STR_RES__MIXER 373  // mixer
#define STR_RES__LFO 374  // lfo
#define STR_RES__FILTER_1 375  // filter 1
#define STR_RES__FILTER_2 376  // filter 2
#define STR_RES__ENVELOPE 377  // envelope
#define STR_RES_ARPEGGIATOR 378  // arpeggiator
#define STR_RES_MULTI 379  // multi
#define STR_RES__CLOCK 380  // clock
#define STR_RES_PERFORMANCE 381  // performance
#define STR_RES__SYSTEM 382  // system
#define STR_RES_PT_X_PATCH 383  // pt X patch
#define STR_RES_PT_X_SEQUENCE 384  // pt X sequence
#define STR_RES_PT_X_PROGRAM 385  // pt X program
#define STR_RES_RANDOMIZE 386  // randomize
#define STR_RES_INIT 387  // init
#define STR_RES_PATCH 388  // PATCH
#define STR_RES_SEQUENCE 389  // SEQUENCE
#define STR_RES_PROGRAM 390  // PROGRAM
#define STR_RES__MULTI 391  // MULTI
#define STR_RES____ 392  // ___
#define STR_RES_EQUAL 393  // equal
#define STR_RES_JUST 394  // just
#define STR_RES_PYTHAGOREAN 395  // pythagorean
#define STR_RES_1_4_EB 396  // 1/4 eb
#define STR_RES_1_4_E 397  // 1/4 e
#define STR_RES_1_4_EA 398  // 1/4 ea
#define STR_RES_BHAIRAV 399  // bhairav
#define STR_RES_GUNAKRI 400  // gunakri
#define STR_RES_MARWA 401  // marwa
#define STR_RES_SHREE 402  // shree
#define STR_RES_PURVI 403  // purvi
#define STR_RES_BILAWAL 404  // bilawal
#define STR_RES_YAMAN 405  // yaman
#define STR_RES_KAFI 406  // kafi
#define STR_RES_BHIMPALASREE 407  // bhimpalasree
#define STR_RES_DARBARI 408  // darbari
#define STR_RES_BAGESHREE 409  // bageshree
#define STR_RES_RAGESHREE 410  // rageshree
#define STR_RES_KHAMAJ 411  // khamaj
#define STR_RES_MIMAL 412  // mi'mal
#define STR_RES_PARAMESHWARI 413  // parameshwari
#define STR_RES_RANGESHWARI 414  // rangeshwari
#define STR_RES_GANGESHWARI 415  // gangeshwari
#define STR_RES_KAMESHWARI 416  // kameshwari
#define STR_RES_PA__KAFI 417  // pa. kafi
#define STR_RES_NATBHAIRAV 418  // natbhairav
#define STR_RES_M_KAUNS 419  // m.kauns
#define STR_RES_BAIRAGI 420  // bairagi
#define STR_RES_B_TODI 421  // b.todi
#define STR_RES_CHANDRADEEP 422  // chandradeep
#define STR_RES_KAUSHIK_TODI 423  // kaushik todi
#define STR_RES_JOGESHWARI 424  // jogeshwari
#define STR_RES_RASIA 425  // rasia
#define LUT_RES_LFO_INCREMENTS 0
#define LUT_RES_LFO_INCREMENTS_SIZE 128
#define LUT_RES_SCALE_JUST 1
#define LUT_RES_SCALE_JUST_SIZE 12
#define LUT_RES_SCALE_PYTHAGOREAN 2
#define LUT_RES_SCALE_PYTHAGOREAN_SIZE 12
#define LUT_RES_SCALE_1_4_EB 3
#define LUT_RES_SCALE_1_4_EB_SIZE 12
#define LUT_RES_SCALE_1_4_E 4
#define LUT_RES_SCALE_1_4_E_SIZE 12
#define LUT_RES_SCALE_1_4_EA 5
#define LUT_RES_SCALE_1_4_EA_SIZE 12
#define LUT_RES_SCALE_BHAIRAV 6
#define LUT_RES_SCALE_BHAIRAV_SIZE 12
#define LUT_RES_SCALE_GUNAKRI 7
#define LUT_RES_SCALE_GUNAKRI_SIZE 12
#define LUT_RES_SCALE_MARWA 8
#define LUT_RES_SCALE_MARWA_SIZE 12
#define LUT_RES_SCALE_SHREE 9
#define LUT_RES_SCALE_SHREE_SIZE 12
#define LUT_RES_SCALE_PURVI 10
#define LUT_RES_SCALE_PURVI_SIZE 12
#define LUT_RES_SCALE_BILAWAL 11
#define LUT_RES_SCALE_BILAWAL_SIZE 12
#define LUT_RES_SCALE_YAMAN 12
#define LUT_RES_SCALE_YAMAN_SIZE 12
#define LUT_RES_SCALE_KAFI 13
#define LUT_RES_SCALE_KAFI_SIZE 12
#define LUT_RES_SCALE_BHIMPALASREE 14
#define LUT_RES_SCALE_BHIMPALASREE_SIZE 12
#define LUT_RES_SCALE_DARBARI 15
#define LUT_RES_SCALE_DARBARI_SIZE 12
#define LUT_RES_SCALE_BAGESHREE 16
#define LUT_RES_SCALE_BAGESHREE_SIZE 12
#define LUT_RES_SCALE_RAGESHREE 17
#define LUT_RES_SCALE_RAGESHREE_SIZE 12
#define LUT_RES_SCALE_KHAMAJ 18
#define LUT_RES_SCALE_KHAMAJ_SIZE 12
#define LUT_RES_SCALE_MIMAL 19
#define LUT_RES_SCALE_MIMAL_SIZE 12
#define LUT_RES_SCALE_PARAMESHWARI 20
#define LUT_RES_SCALE_PARAMESHWARI_SIZE 12
#define LUT_RES_SCALE_RANGESHWARI 21
#define LUT_RES_SCALE_RANGESHWARI_SIZE 12
#define LUT_RES_SCALE_GANGESHWARI 22
#define LUT_RES_SCALE_GANGESHWARI_SIZE 12
#define LUT_RES_SCALE_KAMESHWARI 23
#define LUT_RES_SCALE_KAMESHWARI_SIZE 12
#define LUT_RES_SCALE_PA__KAFI 24
#define LUT_RES_SCALE_PA__KAFI_SIZE 12
#define LUT_RES_SCALE_NATBHAIRAV 25
#define LUT_RES_SCALE_NATBHAIRAV_SIZE 12
#define LUT_RES_SCALE_M_KAUNS 26
#define LUT_RES_SCALE_M_KAUNS_SIZE 12
#define LUT_RES_SCALE_BAIRAGI 27
#define LUT_RES_SCALE_BAIRAGI_SIZE 12
#define LUT_RES_SCALE_B_TODI 28
#define LUT_RES_SCALE_B_TODI_SIZE 12
#define LUT_RES_SCALE_CHANDRADEEP 29
#define LUT_RES_SCALE_CHANDRADEEP_SIZE 12
#define LUT_RES_SCALE_KAUSHIK_TODI 30
#define LUT_RES_SCALE_KAUSHIK_TODI_SIZE 12
#define LUT_RES_SCALE_JOGESHWARI 31
#define LUT_RES_SCALE_JOGESHWARI_SIZE 12
#define LUT_RES_SCALE_RASIA 32
#define LUT_RES_SCALE_RASIA_SIZE 12
#define LUT_RES_ARPEGGIATOR_PATTERNS 33
#define LUT_RES_ARPEGGIATOR_PATTERNS_SIZE 22
#define LUT_RES_GROOVE_SWING 34
#define LUT_RES_GROOVE_SWING_SIZE 16
#define LUT_RES_GROOVE_SHUFFLE 35
#define LUT_RES_GROOVE_SHUFFLE_SIZE 16
#define LUT_RES_GROOVE_PUSH 36
#define LUT_RES_GROOVE_PUSH_SIZE 16
#define LUT_RES_GROOVE_LAG 37
#define LUT_RES_GROOVE_LAG_SIZE 16
#define LUT_RES_GROOVE_HUMAN 38
#define LUT_RES_GROOVE_HUMAN_SIZE 16
#define LUT_RES_GROOVE_MONKEY 39
#define LUT_RES_GROOVE_MONKEY_SIZE 16
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 56
#define WAV_RES_LFO_WAVEFORMS 0
#define WAV_RES_LFO_WAVEFORMS_SIZE 2064
typedef avrlib::ResourcesManager<
    ResourceId,
    avrlib::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace ambika

#endif  // CONTROLLER_RESOURCES_H_
