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
#define STR_RES_SPRM 24  // sprm
#define STR_RES_SPREAD_MODE 25  // spread mode
#define STR_RES_STCK 26  // stck
#define STR_RES_CNTR 27  // cntr
#define STR_RES_WIDE 28  // wide
#define STR_RES_SUB 29  // sub-
#define STR_RES_ATTACK 30  // attack
#define STR_RES_DECAY 31  // decay
#define STR_RES_SUSTAIN 32  // sustain
#define STR_RES_RELEASE 33  // release
#define STR_RES_TRIGGER 34  // trigger
#define STR_RES_RATE 35  // rate
#define STR_RES_LFO_EG 36  // lfo/eg
#define STR_RES_VOICE_LFO 37  // voice lfo
#define STR_RES_SOURCE 38  // source
#define STR_RES_DESTINATION 39  // destination
#define STR_RES_IN1 40  // in1
#define STR_RES_IN2 41  // in2
#define STR_RES_MODULATION 42  // modulation
#define STR_RES_MODUL_ 43  // modul.
#define STR_RES__MODULATION 44  // modulation
#define STR_RES_MODIFIER 45  // modifier
#define STR_RES_MODIF_ 46  // modif.
#define STR_RES_VOLUME 47  // volume
#define STR_RES_OCTAVE 48  // octave
#define STR_RES_SPREAD 49  // spread
#define STR_RES_LEGATO 50  // legato
#define STR_RES_PORTAMENTO 51  // portamento
#define STR_RES_ARP_SEQ 52  // arp/seq
#define STR_RES_RAGA 53  // raga
#define STR_RES_DIRECTION 54  // direction
#define STR_RES_PATTERN 55  // pattern
#define STR_RES_CHANNEL 56  // channel
#define STR_RES_PART 57  // part
#define STR_RES_BPM 58  // bpm
#define STR_RES_LTCH 59  // ltch
#define STR_RES_LATCH 60  // latch
#define STR_RES_LOW 61  // low
#define STR_RES_HIGH 62  // high
#define STR_RES_GRID 63  // grid
#define STR_RES_SEQ1_LEN 64  // seq1 len
#define STR_RES_SEQ2_LEN 65  // seq2 len
#define STR_RES_PATT_LEN 66  // patt len
#define STR_RES_LEN1 67  // len1
#define STR_RES_LEN2 68  // len2
#define STR_RES_LENP 69  // lenp
#define STR_RES_GROOVE 70  // groove
#define STR_RES_MIDI 71  // midi
#define STR_RES_SNAP 72  // snap
#define STR_RES_HELP 73  // help
#define STR_RES_AUTO_BACKUP 74  // auto backup
#define STR_RES_LEDS 75  // leds
#define STR_RES_CARD_LEDS 76  // card leds
#define STR_RES_SWAP_COLORS 77  // swap colors
#define STR_RES_INPT_FILTER 78  // inpt filter
#define STR_RES_OUTP_MODE 79  // outp mode
#define STR_RES_EXT 80  // ext
#define STR_RES_OMNI 81  // omni
#define STR_RES_AMNT 82  // amnt
#define STR_RES_SRCE 83  // srce
#define STR_RES_OCT 84  // oct
#define STR_RES_SPRD 85  // sprd
#define STR_RES_A_SQ 86  // a/sq
#define STR_RES_OCTV 87  // octv
#define STR_RES_OFF 88  // off
#define STR_RES_ON 89  // on
#define STR_RES_NONE 90  // none
#define STR_RES_SAW 91  // saw
#define STR_RES_SQUARE 92  // square
#define STR_RES_TRIANGLE 93  // triangle
#define STR_RES_SINE 94  // sine
#define STR_RES_ZSAW 95  // zsaw
#define STR_RES_LPZSAW 96  // lpzsaw
#define STR_RES_PKZSAW 97  // pkzsaw
#define STR_RES_BPZSAW 98  // bpzsaw
#define STR_RES_HPZSAW 99  // hpzsaw
#define STR_RES_LPZPULSE 100  // lpzpulse
#define STR_RES_PKZPULSE 101  // pkzpulse
#define STR_RES_BPZPULSE 102  // bpzpulse
#define STR_RES_HPZPULSE 103  // hpzpulse
#define STR_RES_ZTRIANGLE 104  // ztriangle
#define STR_RES_PAD 105  // pad
#define STR_RES_FM 106  // fm
#define STR_RES_8BITS 107  // 8bits
#define STR_RES_PWM 108  // pwm
#define STR_RES_NOISE 109  // noise
#define STR_RES_VOWEL 110  // vowel
#define STR_RES_MALE 111  // male
#define STR_RES_FEMALE 112  // female
#define STR_RES_CHOIR 113  // choir
#define STR_RES_TAMPURA 114  // tampura
#define STR_RES_BOWED 115  // bowed
#define STR_RES_CELLO 116  // cello
#define STR_RES_VIBES 117  // vibes
#define STR_RES_SLAP 118  // slap
#define STR_RES_EPIANO 119  // epiano
#define STR_RES_ORGAN 120  // organ
#define STR_RES_WAVES 121  // waves
#define STR_RES_DIGITAL 122  // digital
#define STR_RES_DRONE_1 123  // drone 1
#define STR_RES_DRONE_2 124  // drone 2
#define STR_RES_METALLIC 125  // metallic
#define STR_RES_BELL 126  // bell
#define STR_RES_WAVQUENCE 127  // wavquence
#define STR_RES_OLDSAW 128  // oldsaw
#define STR_RES_QPWM 129  // qpwm
#define STR_RES_FMFB 130  // fmfb
#define STR_RES_CSAW 131  // csaw
#define STR_RES_VOWEL_2 132  // vowel 2
#define STR_RES_TRI 133  // tri
#define STR_RES_SQR 134  // sqr
#define STR_RES_S_H 135  // s&h
#define STR_RES_RAMP 136  // ramp
#define STR_RES__SINE 137  // sine
#define STR_RES_HRM2 138  // hrm2
#define STR_RES_HRM3 139  // hrm3
#define STR_RES_HRM5 140  // hrm5
#define STR_RES_GRG1 141  // grg1
#define STR_RES_GRG2 142  // grg2
#define STR_RES_BAT1 143  // bat1
#define STR_RES_BAT2 144  // bat2
#define STR_RES_SPK1 145  // spk1
#define STR_RES_SPK2 146  // spk2
#define STR_RES_LSAW 147  // lsaw
#define STR_RES_LSQR 148  // lsqr
#define STR_RES_RSAW 149  // rsaw
#define STR_RES_RSQR 150  // rsqr
#define STR_RES_STP1 151  // stp1
#define STR_RES_STP2 152  // stp2
#define STR_RES___OFF 153  // off
#define STR_RES_SYNC 154  // sync
#define STR_RES_RINGMOD 155  // ringmod
#define STR_RES_XOR 156  // xor
#define STR_RES_FOLD 157  // fold
#define STR_RES_BITS 158  // bits
#define STR_RES_SQU1 159  // squ1
#define STR_RES_TRI1 160  // tri1
#define STR_RES_PUL1 161  // pul1
#define STR_RES_SQU2 162  // squ2
#define STR_RES_TRI2 163  // tri2
#define STR_RES_PUL2 164  // pul2
#define STR_RES_CLICK 165  // click
#define STR_RES_GLITCH 166  // glitch
#define STR_RES_BLOW 167  // blow
#define STR_RES_METAL 168  // metal
#define STR_RES_POP 169  // pop
#define STR_RES_ENV1 170  // env1
#define STR_RES_ENV2 171  // env2
#define STR_RES_ENV3 172  // env3
#define STR_RES_LFO1 173  // lfo1
#define STR_RES_LFO2 174  // lfo2
#define STR_RES_LFO3 175  // lfo3
#define STR_RES_LFO4 176  // lfo4
#define STR_RES_MOD1 177  // mod1
#define STR_RES_MOD2 178  // mod2
#define STR_RES_MOD3 179  // mod3
#define STR_RES_MOD4 180  // mod4
#define STR_RES_SEQ1 181  // seq1
#define STR_RES_SEQ2 182  // seq2
#define STR_RES_ARP 183  // arp
#define STR_RES_VELO 184  // velo
#define STR_RES_AFTR 185  // aftr
#define STR_RES_BEND 186  // bend
#define STR_RES_MWHL 187  // mwhl
#define STR_RES_WHL2 188  // whl2
#define STR_RES_PDAL 189  // pdal
#define STR_RES_NOTE 190  // note
#define STR_RES_GATE 191  // gate
#define STR_RES_NOIS 192  // nois
#define STR_RES_RAND 193  // rand
#define STR_RES_E256 194  // =256
#define STR_RES_E128 195  // =128
#define STR_RES_E64 196  // =64
#define STR_RES_E32 197  // =32
#define STR_RES_E16 198  // =16
#define STR_RES_E8 199  // =8
#define STR_RES_E4 200  // =4
#define STR_RES_PRM1 201  // prm1
#define STR_RES_PRM2 202  // prm2
#define STR_RES_OSC1 203  // osc1
#define STR_RES_OSC2 204  // osc2
#define STR_RES_31S2 205  // 1+2
#define STR_RES_VIBR 206  // vibr
#define STR_RES_MIX 207  // mix
#define STR_RES_XMOD 208  // xmod
#define STR_RES__NOIS 209  // nois
#define STR_RES__SUB 210  // sub
#define STR_RES_FUZZ 211  // fuzz
#define STR_RES_CRSH 212  // crsh
#define STR_RES_FREQ 213  // freq
#define STR_RES_RESO 214  // reso
#define STR_RES_ATTK 215  // attk
#define STR_RES_DECA 216  // deca
#define STR_RES_RELE 217  // rele
#define STR_RES__LFO4 218  // lfo4
#define STR_RES_VCA 219  // vca
#define STR_RES_ENV_1 220  // env 1
#define STR_RES_ENV_2 221  // env 2
#define STR_RES_ENV_3 222  // env 3
#define STR_RES_LFO_1 223  // lfo 1
#define STR_RES_LFO_2 224  // lfo 2
#define STR_RES_LFO_3 225  // lfo 3
#define STR_RES_LFO_4 226  // lfo 4
#define STR_RES_MOD__1 227  // mod. 1
#define STR_RES_MOD__2 228  // mod. 2
#define STR_RES_MOD__3 229  // mod. 3
#define STR_RES_MOD__4 230  // mod. 4
#define STR_RES_SEQ__1 231  // seq. 1
#define STR_RES_SEQ__2 232  // seq. 2
#define STR_RES__ARP 233  // arp
#define STR_RES__VELO 234  // velo
#define STR_RES_AFTTCH 235  // afttch
#define STR_RES_BENDER 236  // bender
#define STR_RES_MWHEEL 237  // mwheel
#define STR_RES_WHEEL2 238  // wheel2
#define STR_RES_PEDAL 239  // pedal
#define STR_RES__NOTE 240  // note
#define STR_RES__GATE 241  // gate
#define STR_RES__NOISE 242  // noise
#define STR_RES_RANDOM 243  // random
#define STR_RES_E_256 244  // = 256
#define STR_RES_E_32 245  // = 32
#define STR_RES_E_16 246  // = 16
#define STR_RES_E_8 247  // = 8
#define STR_RES_E_4 248  // = 4
#define STR_RES_PARAM_1 249  // param 1
#define STR_RES_PARAM_2 250  // param 2
#define STR_RES_OSC_1 251  // osc 1
#define STR_RES_OSC_2 252  // osc 2
#define STR_RES_OSC_1S2 253  // osc 1+2
#define STR_RES_VIBRATO 254  // vibrato
#define STR_RES__MIX 255  // mix
#define STR_RES__XMOD 256  // xmod
#define STR_RES___NOISE 257  // noise
#define STR_RES_SUBOSC 258  // subosc
#define STR_RES__FUZZ 259  // fuzz
#define STR_RES_CRUSH 260  // crush
#define STR_RES_FREQUENCY 261  // frequency
#define STR_RES__RESO 262  // reso
#define STR_RES__ATTACK 263  // attack
#define STR_RES__DECAY 264  // decay
#define STR_RES__RELEASE 265  // release
#define STR_RES__LFO_4 266  // lfo 4
#define STR_RES__VCA 267  // vca
#define STR_RES_LP 268  // lp
#define STR_RES_BP 269  // bp
#define STR_RES_HP 270  // hp
#define STR_RES_NT 271  // nt
#define STR_RES_FREE 272  // free
#define STR_RES_ENVTLFO 273  // env~lfo
#define STR_RES_LFOTENV 274  // lfo~env
#define STR_RES_STEP_SEQ 275  // step seq
#define STR_RES_ARPEGGIO 276  // arpeggio
#define STR_RES__PATTERN 277  // pattern
#define STR_RES__OFF 278  // off
#define STR_RES_ADD 279  // add
#define STR_RES_PROD 280  // prod
#define STR_RES_ATTN 281  // attn
#define STR_RES_MAX 282  // max
#define STR_RES_MIN 283  // min
#define STR_RES__XOR 284  // xor
#define STR_RES_GE 285  // >=
#define STR_RES_LE 286  // <=
#define STR_RES_QTZ 287  // qtz
#define STR_RES_LAG 288  // lag
#define STR_RES_MONO 289  // mono
#define STR_RES_POLY 290  // poly
#define STR_RES_2X_UNISON 291  // 2x unison
#define STR_RES_CYCLIC 292  // cyclic
#define STR_RES_CHAIN 293  // chain
#define STR_RES_3X_UNISON 294  // 3x unison
#define STR_RES_4X_UNISON 295  // 4x unison
#define STR_RES_UP 296  // up
#define STR_RES_DOWN 297  // down
#define STR_RES_UP_DOWN 298  // up&down
#define STR_RES_PLAYED 299  // played
#define STR_RES__RANDOM 300  // random
#define STR_RES_CHORD 301  // chord
#define STR_RES_1_1 302  // 1/1
#define STR_RES_3_4 303  // 3/4
#define STR_RES_2_3 304  // 2/3
#define STR_RES_1_2 305  // 1/2
#define STR_RES_3_8 306  // 3/8
#define STR_RES_1_3 307  // 1/3
#define STR_RES_1_4 308  // 1/4
#define STR_RES_1_6 309  // 1/6
#define STR_RES_1_8 310  // 1/8
#define STR_RES_1_12 311  // 1/12
#define STR_RES_1_16 312  // 1/16
#define STR_RES_1_24 313  // 1/24
#define STR_RES_1_32 314  // 1/32
#define STR_RES_1_48 315  // 1/48
#define STR_RES_1_96 316  // 1/96
#define STR_RES_THRU 317  // thru
#define STR_RES_SEQUENCER 318  // sequencer
#define STR_RES_CONTROLLR 319  // controllr
#define STR_RES__CHAIN 320  // chain
#define STR_RES_FULL 321  // full
#define STR_RES_____ 322  // ....
#define STR_RES____S 323  // ...s
#define STR_RES___P_ 324  // ..p.
#define STR_RES___PS 325  // ..ps
#define STR_RES__N__ 326  // .n..
#define STR_RES__N_S 327  // .n.s
#define STR_RES__NP_ 328  // .np.
#define STR_RES__NPS 329  // .nps
#define STR_RES_C___ 330  // c...
#define STR_RES_C__S 331  // c..s
#define STR_RES_C_P_ 332  // c.p.
#define STR_RES_C_PS 333  // c.ps
#define STR_RES_CN__ 334  // cn..
#define STR_RES_CN_S 335  // cn.s
#define STR_RES_CNP_ 336  // cnp.
#define STR_RES_CNPS 337  // cnps
#define STR_RES_SWING 338  // swing
#define STR_RES_SHUFFLE 339  // shuffle
#define STR_RES_PUSH 340  // push
#define STR_RES__LAG 341  // lag
#define STR_RES_HUMAN 342  // human
#define STR_RES_MONKEY 343  // monkey
#define STR_RES_OSCILLATOR_1 344  // oscillator 1
#define STR_RES_OSCILLATOR_2 345  // oscillator 2
#define STR_RES_MIXER 346  // mixer
#define STR_RES_LFO 347  // lfo
#define STR_RES_FILTER_1 348  // filter 1
#define STR_RES_FILTER_2 349  // filter 2
#define STR_RES_ENVELOPE 350  // envelope
#define STR_RES_ARPEGGIATOR 351  // arpeggiator
#define STR_RES_MULTI 352  // multi
#define STR_RES_CLOCK 353  // clock
#define STR_RES_PERFORMANCE 354  // performance
#define STR_RES_SYSTEM 355  // system
#define STR_RES_PT_X_PATCH 356  // pt X patch
#define STR_RES_PT_X_SEQUENCE 357  // pt X sequence
#define STR_RES_PT_X_PROGRAM 358  // pt X program
#define STR_RES_RANDOMIZE 359  // randomize
#define STR_RES_INIT 360  // init
#define STR_RES_PATCH 361  // PATCH
#define STR_RES_SEQUENCE 362  // SEQUENCE
#define STR_RES_PROGRAM 363  // PROGRAM
#define STR_RES__MULTI 364  // MULTI
#define STR_RES____ 365  // ___
#define STR_RES_EQUAL 366  // equal
#define STR_RES_JUST 367  // just
#define STR_RES_PYTHAGOREAN 368  // pythagorean
#define STR_RES_1_4_EB 369  // 1/4 eb
#define STR_RES_1_4_E 370  // 1/4 e
#define STR_RES_1_4_EA 371  // 1/4 ea
#define STR_RES_BHAIRAV 372  // bhairav
#define STR_RES_GUNAKRI 373  // gunakri
#define STR_RES_MARWA 374  // marwa
#define STR_RES_SHREE 375  // shree
#define STR_RES_PURVI 376  // purvi
#define STR_RES_BILAWAL 377  // bilawal
#define STR_RES_YAMAN 378  // yaman
#define STR_RES_KAFI 379  // kafi
#define STR_RES_BHIMPALASREE 380  // bhimpalasree
#define STR_RES_DARBARI 381  // darbari
#define STR_RES_BAGESHREE 382  // bageshree
#define STR_RES_RAGESHREE 383  // rageshree
#define STR_RES_KHAMAJ 384  // khamaj
#define STR_RES_MIMAL 385  // mi'mal
#define STR_RES_PARAMESHWARI 386  // parameshwari
#define STR_RES_RANGESHWARI 387  // rangeshwari
#define STR_RES_GANGESHWARI 388  // gangeshwari
#define STR_RES_KAMESHWARI 389  // kameshwari
#define STR_RES_PA__KAFI 390  // pa. kafi
#define STR_RES_NATBHAIRAV 391  // natbhairav
#define STR_RES_M_KAUNS 392  // m.kauns
#define STR_RES_BAIRAGI 393  // bairagi
#define STR_RES_B_TODI 394  // b.todi
#define STR_RES_CHANDRADEEP 395  // chandradeep
#define STR_RES_KAUSHIK_TODI 396  // kaushik todi
#define STR_RES_JOGESHWARI 397  // jogeshwari
#define STR_RES_RASIA 398  // rasia
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
