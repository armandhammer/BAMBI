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
#define STR_RES_ATTACK 29  // attack
#define STR_RES_DECAY 30  // decay
#define STR_RES_SUSTAIN 31  // sustain
#define STR_RES_RELEASE 32  // release
#define STR_RES_TRIGGER 33  // trigger
#define STR_RES_RATE 34  // rate
#define STR_RES_LFO_EG 35  // lfo/eg
#define STR_RES_VOICE_LFO 36  // voice lfo
#define STR_RES_SOURCE 37  // source
#define STR_RES_DESTINATION 38  // destination
#define STR_RES_IN1 39  // in1
#define STR_RES_IN2 40  // in2
#define STR_RES_MODULATION 41  // modulation
#define STR_RES_MODUL_ 42  // modul.
#define STR_RES__MODULATION 43  // modulation
#define STR_RES_MODIFIER 44  // modifier
#define STR_RES_MODIF_ 45  // modif.
#define STR_RES_VOLUME 46  // volume
#define STR_RES_OCTAVE 47  // octave
#define STR_RES_SPREAD 48  // spread
#define STR_RES_LEGATO 49  // legato
#define STR_RES_PORTAMENTO 50  // portamento
#define STR_RES_ARP_SEQ 51  // arp/seq
#define STR_RES_RAGA 52  // raga
#define STR_RES_DIRECTION 53  // direction
#define STR_RES_PATTERN 54  // pattern
#define STR_RES_CHANNEL 55  // channel
#define STR_RES_PART 56  // part
#define STR_RES_BPM 57  // bpm
#define STR_RES_LTCH 58  // ltch
#define STR_RES_LATCH 59  // latch
#define STR_RES_LOW 60  // low
#define STR_RES_HIGH 61  // high
#define STR_RES_GRID 62  // grid
#define STR_RES_SEQ1_LEN 63  // seq1 len
#define STR_RES_SEQ2_LEN 64  // seq2 len
#define STR_RES_PATT_LEN 65  // patt len
#define STR_RES_LEN1 66  // len1
#define STR_RES_LEN2 67  // len2
#define STR_RES_LENP 68  // lenp
#define STR_RES_GROOVE 69  // groove
#define STR_RES_MIDI 70  // midi
#define STR_RES_SNAP 71  // snap
#define STR_RES_HELP 72  // help
#define STR_RES_AUTO_BACKUP 73  // auto backup
#define STR_RES_LEDS 74  // leds
#define STR_RES_CARD_LEDS 75  // card leds
#define STR_RES_SWAP_COLORS 76  // swap colors
#define STR_RES_INPT_FILTER 77  // inpt filter
#define STR_RES_OUTP_MODE 78  // outp mode
#define STR_RES_EXT 79  // ext
#define STR_RES_OMNI 80  // omni
#define STR_RES_AMNT 81  // amnt
#define STR_RES_SRCE 82  // srce
#define STR_RES_OCT 83  // oct
#define STR_RES_SPRD 84  // sprd
#define STR_RES_A_SQ 85  // a/sq
#define STR_RES_OCTV 86  // octv
#define STR_RES_OFF 87  // off
#define STR_RES_ON 88  // on
#define STR_RES_NONE 89  // none
#define STR_RES_SAW 90  // saw
#define STR_RES_SQUARE 91  // square
#define STR_RES_TRIANGLE 92  // triangle
#define STR_RES_SINE 93  // sine
#define STR_RES_ZSAW 94  // zsaw
#define STR_RES_LPZSAW 95  // lpzsaw
#define STR_RES_PKZSAW 96  // pkzsaw
#define STR_RES_BPZSAW 97  // bpzsaw
#define STR_RES_HPZSAW 98  // hpzsaw
#define STR_RES_LPZPULSE 99  // lpzpulse
#define STR_RES_PKZPULSE 100  // pkzpulse
#define STR_RES_BPZPULSE 101  // bpzpulse
#define STR_RES_HPZPULSE 102  // hpzpulse
#define STR_RES_ZTRIANGLE 103  // ztriangle
#define STR_RES_PAD 104  // pad
#define STR_RES_FM 105  // fm
#define STR_RES_8BITS 106  // 8bits
#define STR_RES_PWM 107  // pwm
#define STR_RES_NOISE 108  // noise
#define STR_RES_VOWEL 109  // vowel
#define STR_RES_MALE 110  // male
#define STR_RES_FEMALE 111  // female
#define STR_RES_CHOIR 112  // choir
#define STR_RES_TAMPURA 113  // tampura
#define STR_RES_BOWED 114  // bowed
#define STR_RES_CELLO 115  // cello
#define STR_RES_VIBES 116  // vibes
#define STR_RES_SLAP 117  // slap
#define STR_RES_EPIANO 118  // epiano
#define STR_RES_ORGAN 119  // organ
#define STR_RES_WAVES 120  // waves
#define STR_RES_DIGITAL 121  // digital
#define STR_RES_DRONE_1 122  // drone 1
#define STR_RES_DRONE_2 123  // drone 2
#define STR_RES_METALLIC 124  // metallic
#define STR_RES_BELL 125  // bell
#define STR_RES_WAVQUENCE 126  // wavquence
#define STR_RES_OLDSAW 127  // oldsaw
#define STR_RES_QPWM 128  // qpwm
#define STR_RES_FMFB 129  // fmfb
#define STR_RES_CSAW 130  // csaw
#define STR_RES_VOWEL_2 131  // vowel 2
#define STR_RES_TRI 132  // tri
#define STR_RES_SQR 133  // sqr
#define STR_RES_S_H 134  // s&h
#define STR_RES_RAMP 135  // ramp
#define STR_RES__SINE 136  // sine
#define STR_RES_HRM2 137  // hrm2
#define STR_RES_HRM3 138  // hrm3
#define STR_RES_HRM5 139  // hrm5
#define STR_RES_GRG1 140  // grg1
#define STR_RES_GRG2 141  // grg2
#define STR_RES_BAT1 142  // bat1
#define STR_RES_BAT2 143  // bat2
#define STR_RES_SPK1 144  // spk1
#define STR_RES_SPK2 145  // spk2
#define STR_RES_LSAW 146  // lsaw
#define STR_RES_LSQR 147  // lsqr
#define STR_RES_RSAW 148  // rsaw
#define STR_RES_RSQR 149  // rsqr
#define STR_RES_STP1 150  // stp1
#define STR_RES_STP2 151  // stp2
#define STR_RES___OFF 152  // off
#define STR_RES_SYNC 153  // sync
#define STR_RES_RINGMOD 154  // ringmod
#define STR_RES_XOR 155  // xor
#define STR_RES_FOLD 156  // fold
#define STR_RES_BITS 157  // bits
#define STR_RES_SQU1 158  // squ1
#define STR_RES_TRI1 159  // tri1
#define STR_RES_PUL1 160  // pul1
#define STR_RES_SQU2 161  // squ2
#define STR_RES_TRI2 162  // tri2
#define STR_RES_PUL2 163  // pul2
#define STR_RES_CLICK 164  // click
#define STR_RES_GLITCH 165  // glitch
#define STR_RES_BLOW 166  // blow
#define STR_RES_METAL 167  // metal
#define STR_RES_POP 168  // pop
#define STR_RES_ENV1 169  // env1
#define STR_RES_ENV2 170  // env2
#define STR_RES_ENV3 171  // env3
#define STR_RES_LFO1 172  // lfo1
#define STR_RES_LFO2 173  // lfo2
#define STR_RES_LFO3 174  // lfo3
#define STR_RES_LFO4 175  // lfo4
#define STR_RES_MOD1 176  // mod1
#define STR_RES_MOD2 177  // mod2
#define STR_RES_MOD3 178  // mod3
#define STR_RES_MOD4 179  // mod4
#define STR_RES_SEQ1 180  // seq1
#define STR_RES_SEQ2 181  // seq2
#define STR_RES_ARP 182  // arp
#define STR_RES_VELO 183  // velo
#define STR_RES_AFTR 184  // aftr
#define STR_RES_BEND 185  // bend
#define STR_RES_MWHL 186  // mwhl
#define STR_RES_WHL2 187  // whl2
#define STR_RES_PDAL 188  // pdal
#define STR_RES_NOTE 189  // note
#define STR_RES_GATE 190  // gate
#define STR_RES_NOIS 191  // nois
#define STR_RES_RAND 192  // rand
#define STR_RES_E256 193  // =256
#define STR_RES_E128 194  // =128
#define STR_RES_E64 195  // =64
#define STR_RES_E32 196  // =32
#define STR_RES_E16 197  // =16
#define STR_RES_E8 198  // =8
#define STR_RES_E4 199  // =4
#define STR_RES_PRM1 200  // prm1
#define STR_RES_PRM2 201  // prm2
#define STR_RES_OSC1 202  // osc1
#define STR_RES_OSC2 203  // osc2
#define STR_RES_31S2 204  // 1+2
#define STR_RES_VIBR 205  // vibr
#define STR_RES_MIX 206  // mix
#define STR_RES_XMOD 207  // xmod
#define STR_RES__NOIS 208  // nois
#define STR_RES_SUB 209  // sub
#define STR_RES_FUZZ 210  // fuzz
#define STR_RES_CRSH 211  // crsh
#define STR_RES_FREQ 212  // freq
#define STR_RES_RESO 213  // reso
#define STR_RES_ATTK 214  // attk
#define STR_RES_DECA 215  // deca
#define STR_RES_RELE 216  // rele
#define STR_RES__LFO4 217  // lfo4
#define STR_RES_VCA 218  // vca
#define STR_RES_ENV_1 219  // env 1
#define STR_RES_ENV_2 220  // env 2
#define STR_RES_ENV_3 221  // env 3
#define STR_RES_LFO_1 222  // lfo 1
#define STR_RES_LFO_2 223  // lfo 2
#define STR_RES_LFO_3 224  // lfo 3
#define STR_RES_LFO_4 225  // lfo 4
#define STR_RES_MOD__1 226  // mod. 1
#define STR_RES_MOD__2 227  // mod. 2
#define STR_RES_MOD__3 228  // mod. 3
#define STR_RES_MOD__4 229  // mod. 4
#define STR_RES_SEQ__1 230  // seq. 1
#define STR_RES_SEQ__2 231  // seq. 2
#define STR_RES__ARP 232  // arp
#define STR_RES__VELO 233  // velo
#define STR_RES_AFTTCH 234  // afttch
#define STR_RES_BENDER 235  // bender
#define STR_RES_MWHEEL 236  // mwheel
#define STR_RES_WHEEL2 237  // wheel2
#define STR_RES_PEDAL 238  // pedal
#define STR_RES__NOTE 239  // note
#define STR_RES__GATE 240  // gate
#define STR_RES__NOISE 241  // noise
#define STR_RES_RANDOM 242  // random
#define STR_RES_E_256 243  // = 256
#define STR_RES_E_32 244  // = 32
#define STR_RES_E_16 245  // = 16
#define STR_RES_E_8 246  // = 8
#define STR_RES_E_4 247  // = 4
#define STR_RES_PARAM_1 248  // param 1
#define STR_RES_PARAM_2 249  // param 2
#define STR_RES_OSC_1 250  // osc 1
#define STR_RES_OSC_2 251  // osc 2
#define STR_RES_OSC_1S2 252  // osc 1+2
#define STR_RES_VIBRATO 253  // vibrato
#define STR_RES__MIX 254  // mix
#define STR_RES__XMOD 255  // xmod
#define STR_RES___NOISE 256  // noise
#define STR_RES_SUBOSC 257  // subosc
#define STR_RES__FUZZ 258  // fuzz
#define STR_RES_CRUSH 259  // crush
#define STR_RES_FREQUENCY 260  // frequency
#define STR_RES__RESO 261  // reso
#define STR_RES__ATTACK 262  // attack
#define STR_RES__DECAY 263  // decay
#define STR_RES__RELEASE 264  // release
#define STR_RES__LFO_4 265  // lfo 4
#define STR_RES__VCA 266  // vca
#define STR_RES_LP 267  // lp
#define STR_RES_BP 268  // bp
#define STR_RES_HP 269  // hp
#define STR_RES_NT 270  // nt
#define STR_RES_FREE 271  // free
#define STR_RES_ENVTLFO 272  // env~lfo
#define STR_RES_LFOTENV 273  // lfo~env
#define STR_RES_STEP_SEQ 274  // step seq
#define STR_RES_ARPEGGIO 275  // arpeggio
#define STR_RES__PATTERN 276  // pattern
#define STR_RES__OFF 277  // off
#define STR_RES_ADD 278  // add
#define STR_RES_PROD 279  // prod
#define STR_RES_ATTN 280  // attn
#define STR_RES_MAX 281  // max
#define STR_RES_MIN 282  // min
#define STR_RES__XOR 283  // xor
#define STR_RES_GE 284  // >=
#define STR_RES_LE 285  // <=
#define STR_RES_QTZ 286  // qtz
#define STR_RES_LAG 287  // lag
#define STR_RES_MONO 288  // mono
#define STR_RES_POLY 289  // poly
#define STR_RES_2X_UNISON 290  // 2x unison
#define STR_RES_CYCLIC 291  // cyclic
#define STR_RES_CHAIN 292  // chain
#define STR_RES_UP 293  // up
#define STR_RES_DOWN 294  // down
#define STR_RES_UP_DOWN 295  // up&down
#define STR_RES_PLAYED 296  // played
#define STR_RES__RANDOM 297  // random
#define STR_RES_CHORD 298  // chord
#define STR_RES_1_1 299  // 1/1
#define STR_RES_3_4 300  // 3/4
#define STR_RES_2_3 301  // 2/3
#define STR_RES_1_2 302  // 1/2
#define STR_RES_3_8 303  // 3/8
#define STR_RES_1_3 304  // 1/3
#define STR_RES_1_4 305  // 1/4
#define STR_RES_1_6 306  // 1/6
#define STR_RES_1_8 307  // 1/8
#define STR_RES_1_12 308  // 1/12
#define STR_RES_1_16 309  // 1/16
#define STR_RES_1_24 310  // 1/24
#define STR_RES_1_32 311  // 1/32
#define STR_RES_1_48 312  // 1/48
#define STR_RES_1_96 313  // 1/96
#define STR_RES_THRU 314  // thru
#define STR_RES_SEQUENCER 315  // sequencer
#define STR_RES_CONTROLLR 316  // controllr
#define STR_RES__CHAIN 317  // chain
#define STR_RES_FULL 318  // full
#define STR_RES_____ 319  // ....
#define STR_RES____S 320  // ...s
#define STR_RES___P_ 321  // ..p.
#define STR_RES___PS 322  // ..ps
#define STR_RES__N__ 323  // .n..
#define STR_RES__N_S 324  // .n.s
#define STR_RES__NP_ 325  // .np.
#define STR_RES__NPS 326  // .nps
#define STR_RES_C___ 327  // c...
#define STR_RES_C__S 328  // c..s
#define STR_RES_C_P_ 329  // c.p.
#define STR_RES_C_PS 330  // c.ps
#define STR_RES_CN__ 331  // cn..
#define STR_RES_CN_S 332  // cn.s
#define STR_RES_CNP_ 333  // cnp.
#define STR_RES_CNPS 334  // cnps
#define STR_RES_SWING 335  // swing
#define STR_RES_SHUFFLE 336  // shuffle
#define STR_RES_PUSH 337  // push
#define STR_RES__LAG 338  // lag
#define STR_RES_HUMAN 339  // human
#define STR_RES_MONKEY 340  // monkey
#define STR_RES_OSCILLATOR_1 341  // oscillator 1
#define STR_RES_OSCILLATOR_2 342  // oscillator 2
#define STR_RES_MIXER 343  // mixer
#define STR_RES_LFO 344  // lfo
#define STR_RES_FILTER_1 345  // filter 1
#define STR_RES_FILTER_2 346  // filter 2
#define STR_RES_ENVELOPE 347  // envelope
#define STR_RES_ARPEGGIATOR 348  // arpeggiator
#define STR_RES_MULTI 349  // multi
#define STR_RES_CLOCK 350  // clock
#define STR_RES_PERFORMANCE 351  // performance
#define STR_RES_SYSTEM 352  // system
#define STR_RES_PT_X_PATCH 353  // pt X patch
#define STR_RES_PT_X_SEQUENCE 354  // pt X sequence
#define STR_RES_PT_X_PROGRAM 355  // pt X program
#define STR_RES_RANDOMIZE 356  // randomize
#define STR_RES_INIT 357  // init
#define STR_RES_PATCH 358  // PATCH
#define STR_RES_SEQUENCE 359  // SEQUENCE
#define STR_RES_PROGRAM 360  // PROGRAM
#define STR_RES__MULTI 361  // MULTI
#define STR_RES____ 362  // ___
#define STR_RES_EQUAL 363  // equal
#define STR_RES_JUST 364  // just
#define STR_RES_PYTHAGOREAN 365  // pythagorean
#define STR_RES_1_4_EB 366  // 1/4 eb
#define STR_RES_1_4_E 367  // 1/4 e
#define STR_RES_1_4_EA 368  // 1/4 ea
#define STR_RES_BHAIRAV 369  // bhairav
#define STR_RES_GUNAKRI 370  // gunakri
#define STR_RES_MARWA 371  // marwa
#define STR_RES_SHREE 372  // shree
#define STR_RES_PURVI 373  // purvi
#define STR_RES_BILAWAL 374  // bilawal
#define STR_RES_YAMAN 375  // yaman
#define STR_RES_KAFI 376  // kafi
#define STR_RES_BHIMPALASREE 377  // bhimpalasree
#define STR_RES_DARBARI 378  // darbari
#define STR_RES_BAGESHREE 379  // bageshree
#define STR_RES_RAGESHREE 380  // rageshree
#define STR_RES_KHAMAJ 381  // khamaj
#define STR_RES_MIMAL 382  // mi'mal
#define STR_RES_PARAMESHWARI 383  // parameshwari
#define STR_RES_RANGESHWARI 384  // rangeshwari
#define STR_RES_GANGESHWARI 385  // gangeshwari
#define STR_RES_KAMESHWARI 386  // kameshwari
#define STR_RES_PA__KAFI 387  // pa. kafi
#define STR_RES_NATBHAIRAV 388  // natbhairav
#define STR_RES_M_KAUNS 389  // m.kauns
#define STR_RES_BAIRAGI 390  // bairagi
#define STR_RES_B_TODI 391  // b.todi
#define STR_RES_CHANDRADEEP 392  // chandradeep
#define STR_RES_KAUSHIK_TODI 393  // kaushik todi
#define STR_RES_JOGESHWARI 394  // jogeshwari
#define STR_RES_RASIA 395  // rasia
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
