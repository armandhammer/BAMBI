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
#define STR_RES_ATTACK 21  // attack
#define STR_RES_DECAY 22  // decay
#define STR_RES_SUSTAIN 23  // sustain
#define STR_RES_RELEASE 24  // release
#define STR_RES_TRIGGER 25  // trigger
#define STR_RES_RATE 26  // rate
#define STR_RES_LFO_EG 27  // lfo/eg
#define STR_RES_VOICE_LFO 28  // voice lfo
#define STR_RES_SOURCE 29  // source
#define STR_RES_DESTINATION 30  // destination
#define STR_RES_IN1 31  // in1
#define STR_RES_IN2 32  // in2
#define STR_RES_MODULATION 33  // modulation
#define STR_RES_MODUL_ 34  // modul.
#define STR_RES__MODULATION 35  // modulation
#define STR_RES_MODIFIER 36  // modifier
#define STR_RES_MODIF_ 37  // modif.
#define STR_RES_VOLUME 38  // volume
#define STR_RES_OCTAVE 39  // octave
#define STR_RES_SPREAD 40  // spread
#define STR_RES_LEGATO 41  // legato
#define STR_RES_PORTAMENTO 42  // portamento
#define STR_RES_ARP_SEQ 43  // arp/seq
#define STR_RES_RAGA 44  // raga
#define STR_RES_DIRECTION 45  // direction
#define STR_RES_PATTERN 46  // pattern
#define STR_RES_CHANNEL 47  // channel
#define STR_RES_PART 48  // part
#define STR_RES_BPM 49  // bpm
#define STR_RES_LTCH 50  // ltch
#define STR_RES_LATCH 51  // latch
#define STR_RES_LOW 52  // low
#define STR_RES_HIGH 53  // high
#define STR_RES_GRID 54  // grid
#define STR_RES_SEQ1_LEN 55  // seq1 len
#define STR_RES_SEQ2_LEN 56  // seq2 len
#define STR_RES_PATT_LEN 57  // patt len
#define STR_RES_LEN1 58  // len1
#define STR_RES_LEN2 59  // len2
#define STR_RES_LENP 60  // lenp
#define STR_RES_GROOVE 61  // groove
#define STR_RES_MIDI 62  // midi
#define STR_RES_SNAP 63  // snap
#define STR_RES_HELP 64  // help
#define STR_RES_AUTO_BACKUP 65  // auto backup
#define STR_RES_LEDS 66  // leds
#define STR_RES_CARD_LEDS 67  // card leds
#define STR_RES_SWAP_COLORS 68  // swap colors
#define STR_RES_INPT_FILTER 69  // inpt filter
#define STR_RES_OUTP_MODE 70  // outp mode
#define STR_RES_EXT 71  // ext
#define STR_RES_OMNI 72  // omni
#define STR_RES_AMNT 73  // amnt
#define STR_RES_SRCE 74  // srce
#define STR_RES_OCT 75  // oct
#define STR_RES_SPRD 76  // sprd
#define STR_RES_A_SQ 77  // a/sq
#define STR_RES_OCTV 78  // octv
#define STR_RES_OFF 79  // off
#define STR_RES_ON 80  // on
#define STR_RES_NONE 81  // none
#define STR_RES_SAW 82  // saw
#define STR_RES_SQUARE 83  // square
#define STR_RES_TRIANGLE 84  // triangle
#define STR_RES_SINE 85  // sine
#define STR_RES_ZSAW 86  // zsaw
#define STR_RES_LPZSAW 87  // lpzsaw
#define STR_RES_PKZSAW 88  // pkzsaw
#define STR_RES_BPZSAW 89  // bpzsaw
#define STR_RES_HPZSAW 90  // hpzsaw
#define STR_RES_LPZPULSE 91  // lpzpulse
#define STR_RES_PKZPULSE 92  // pkzpulse
#define STR_RES_BPZPULSE 93  // bpzpulse
#define STR_RES_HPZPULSE 94  // hpzpulse
#define STR_RES_ZTRIANGLE 95  // ztriangle
#define STR_RES_PAD 96  // pad
#define STR_RES_FM 97  // fm
#define STR_RES_8BITS 98  // 8bits
#define STR_RES_PWM 99  // pwm
#define STR_RES_NOISE 100  // noise
#define STR_RES_VOWEL 101  // vowel
#define STR_RES_MALE 102  // male
#define STR_RES_FEMALE 103  // female
#define STR_RES_CHOIR 104  // choir
#define STR_RES_TAMPURA 105  // tampura
#define STR_RES_BOWED 106  // bowed
#define STR_RES_CELLO 107  // cello
#define STR_RES_VIBES 108  // vibes
#define STR_RES_SLAP 109  // slap
#define STR_RES_EPIANO 110  // epiano
#define STR_RES_ORGAN 111  // organ
#define STR_RES_WAVES 112  // waves
#define STR_RES_DIGITAL 113  // digital
#define STR_RES_DRONE_1 114  // drone 1
#define STR_RES_DRONE_2 115  // drone 2
#define STR_RES_METALLIC 116  // metallic
#define STR_RES_BELL 117  // bell
#define STR_RES_WAVQUENCE 118  // wavquence
#define STR_RES_OLDSAW 119  // oldsaw
#define STR_RES_QPWM 120  // qpwm
#define STR_RES_FMFB 121  // fmfb
#define STR_RES_CSAW 122  // csaw
#define STR_RES_VOWEL_2 123  // vowel 2
#define STR_RES_TRI 124  // tri
#define STR_RES_SQR 125  // sqr
#define STR_RES_S_H 126  // s&h
#define STR_RES_RAMP 127  // ramp
#define STR_RES__SINE 128  // sine
#define STR_RES_HRM2 129  // hrm2
#define STR_RES_HRM3 130  // hrm3
#define STR_RES_HRM5 131  // hrm5
#define STR_RES_GRG1 132  // grg1
#define STR_RES_GRG2 133  // grg2
#define STR_RES_BAT1 134  // bat1
#define STR_RES_BAT2 135  // bat2
#define STR_RES_SPK1 136  // spk1
#define STR_RES_SPK2 137  // spk2
#define STR_RES_LSAW 138  // lsaw
#define STR_RES_LSQR 139  // lsqr
#define STR_RES_RSAW 140  // rsaw
#define STR_RES_RSQR 141  // rsqr
#define STR_RES_STP1 142  // stp1
#define STR_RES_STP2 143  // stp2
#define STR_RES___OFF 144  // off
#define STR_RES_SYNC 145  // sync
#define STR_RES_RINGMOD 146  // ringmod
#define STR_RES_XOR 147  // xor
#define STR_RES_FOLD 148  // fold
#define STR_RES_BITS 149  // bits
#define STR_RES_SQU1 150  // squ1
#define STR_RES_TRI1 151  // tri1
#define STR_RES_PUL1 152  // pul1
#define STR_RES_SQU2 153  // squ2
#define STR_RES_TRI2 154  // tri2
#define STR_RES_PUL2 155  // pul2
#define STR_RES_CLICK 156  // click
#define STR_RES_GLITCH 157  // glitch
#define STR_RES_BLOW 158  // blow
#define STR_RES_METAL 159  // metal
#define STR_RES_POP 160  // pop
#define STR_RES_ENV1 161  // env1
#define STR_RES_ENV2 162  // env2
#define STR_RES_ENV3 163  // env3
#define STR_RES_LFO1 164  // lfo1
#define STR_RES_LFO2 165  // lfo2
#define STR_RES_LFO3 166  // lfo3
#define STR_RES_LFO4 167  // lfo4
#define STR_RES_MOD1 168  // mod1
#define STR_RES_MOD2 169  // mod2
#define STR_RES_MOD3 170  // mod3
#define STR_RES_MOD4 171  // mod4
#define STR_RES_SEQ1 172  // seq1
#define STR_RES_SEQ2 173  // seq2
#define STR_RES_ARP 174  // arp
#define STR_RES_VELO 175  // velo
#define STR_RES_AFTR 176  // aftr
#define STR_RES_BEND 177  // bend
#define STR_RES_MWHL 178  // mwhl
#define STR_RES_WHL2 179  // whl2
#define STR_RES_PDAL 180  // pdal
#define STR_RES_NOTE 181  // note
#define STR_RES_GATE 182  // gate
#define STR_RES_NOIS 183  // nois
#define STR_RES_RAND 184  // rand
#define STR_RES_E256 185  // =256
#define STR_RES_E128 186  // =128
#define STR_RES_E64 187  // =64
#define STR_RES_E32 188  // =32
#define STR_RES_E16 189  // =16
#define STR_RES_E8 190  // =8
#define STR_RES_E4 191  // =4
#define STR_RES_PRM1 192  // prm1
#define STR_RES_PRM2 193  // prm2
#define STR_RES_OSC1 194  // osc1
#define STR_RES_OSC2 195  // osc2
#define STR_RES_31S2 196  // 1+2
#define STR_RES_VIBR 197  // vibr
#define STR_RES_MIX 198  // mix
#define STR_RES_XMOD 199  // xmod
#define STR_RES__NOIS 200  // nois
#define STR_RES_SUB 201  // sub
#define STR_RES_FUZZ 202  // fuzz
#define STR_RES_CRSH 203  // crsh
#define STR_RES_FREQ 204  // freq
#define STR_RES_RESO 205  // reso
#define STR_RES_ATTK 206  // attk
#define STR_RES_DECA 207  // deca
#define STR_RES_RELE 208  // rele
#define STR_RES__LFO4 209  // lfo4
#define STR_RES_VCA 210  // vca
#define STR_RES_ENV_1 211  // env 1
#define STR_RES_ENV_2 212  // env 2
#define STR_RES_ENV_3 213  // env 3
#define STR_RES_LFO_1 214  // lfo 1
#define STR_RES_LFO_2 215  // lfo 2
#define STR_RES_LFO_3 216  // lfo 3
#define STR_RES_LFO_4 217  // lfo 4
#define STR_RES_MOD__1 218  // mod. 1
#define STR_RES_MOD__2 219  // mod. 2
#define STR_RES_MOD__3 220  // mod. 3
#define STR_RES_MOD__4 221  // mod. 4
#define STR_RES_SEQ__1 222  // seq. 1
#define STR_RES_SEQ__2 223  // seq. 2
#define STR_RES__ARP 224  // arp
#define STR_RES__VELO 225  // velo
#define STR_RES_AFTTCH 226  // afttch
#define STR_RES_BENDER 227  // bender
#define STR_RES_MWHEEL 228  // mwheel
#define STR_RES_WHEEL2 229  // wheel2
#define STR_RES_PEDAL 230  // pedal
#define STR_RES__NOTE 231  // note
#define STR_RES__GATE 232  // gate
#define STR_RES__NOISE 233  // noise
#define STR_RES_RANDOM 234  // random
#define STR_RES_E_256 235  // = 256
#define STR_RES_E_32 236  // = 32
#define STR_RES_E_16 237  // = 16
#define STR_RES_E_8 238  // = 8
#define STR_RES_E_4 239  // = 4
#define STR_RES_PARAM_1 240  // param 1
#define STR_RES_PARAM_2 241  // param 2
#define STR_RES_OSC_1 242  // osc 1
#define STR_RES_OSC_2 243  // osc 2
#define STR_RES_OSC_1S2 244  // osc 1+2
#define STR_RES_VIBRATO 245  // vibrato
#define STR_RES__MIX 246  // mix
#define STR_RES__XMOD 247  // xmod
#define STR_RES___NOISE 248  // noise
#define STR_RES_SUBOSC 249  // subosc
#define STR_RES__FUZZ 250  // fuzz
#define STR_RES_CRUSH 251  // crush
#define STR_RES_FREQUENCY 252  // frequency
#define STR_RES__RESO 253  // reso
#define STR_RES__ATTACK 254  // attack
#define STR_RES__DECAY 255  // decay
#define STR_RES__RELEASE 256  // release
#define STR_RES__LFO_4 257  // lfo 4
#define STR_RES__VCA 258  // vca
#define STR_RES_LP 259  // lp
#define STR_RES_BP 260  // bp
#define STR_RES_HP 261  // hp
#define STR_RES_NT 262  // nt
#define STR_RES_FREE 263  // free
#define STR_RES_ENVTLFO 264  // env~lfo
#define STR_RES_LFOTENV 265  // lfo~env
#define STR_RES_STEP_SEQ 266  // step seq
#define STR_RES_ARPEGGIO 267  // arpeggio
#define STR_RES__PATTERN 268  // pattern
#define STR_RES__OFF 269  // off
#define STR_RES_ADD 270  // add
#define STR_RES_PROD 271  // prod
#define STR_RES_ATTN 272  // attn
#define STR_RES_MAX 273  // max
#define STR_RES_MIN 274  // min
#define STR_RES__XOR 275  // xor
#define STR_RES_GE 276  // >=
#define STR_RES_LE 277  // <=
#define STR_RES_QTZ 278  // qtz
#define STR_RES_LAG 279  // lag
#define STR_RES_MONO 280  // mono
#define STR_RES_POLY 281  // poly
#define STR_RES_2X_UNISON 282  // 2x unison
#define STR_RES_CYCLIC 283  // cyclic
#define STR_RES_CHAIN 284  // chain
#define STR_RES_UP 285  // up
#define STR_RES_DOWN 286  // down
#define STR_RES_UP_DOWN 287  // up&down
#define STR_RES_PLAYED 288  // played
#define STR_RES__RANDOM 289  // random
#define STR_RES_CHORD 290  // chord
#define STR_RES_1_1 291  // 1/1
#define STR_RES_3_4 292  // 3/4
#define STR_RES_2_3 293  // 2/3
#define STR_RES_1_2 294  // 1/2
#define STR_RES_3_8 295  // 3/8
#define STR_RES_1_3 296  // 1/3
#define STR_RES_1_4 297  // 1/4
#define STR_RES_1_6 298  // 1/6
#define STR_RES_1_8 299  // 1/8
#define STR_RES_1_12 300  // 1/12
#define STR_RES_1_16 301  // 1/16
#define STR_RES_1_24 302  // 1/24
#define STR_RES_1_32 303  // 1/32
#define STR_RES_1_48 304  // 1/48
#define STR_RES_1_96 305  // 1/96
#define STR_RES_THRU 306  // thru
#define STR_RES_SEQUENCER 307  // sequencer
#define STR_RES_CONTROLLR 308  // controllr
#define STR_RES__CHAIN 309  // chain
#define STR_RES_FULL 310  // full
#define STR_RES_____ 311  // ....
#define STR_RES____S 312  // ...s
#define STR_RES___P_ 313  // ..p.
#define STR_RES___PS 314  // ..ps
#define STR_RES__N__ 315  // .n..
#define STR_RES__N_S 316  // .n.s
#define STR_RES__NP_ 317  // .np.
#define STR_RES__NPS 318  // .nps
#define STR_RES_C___ 319  // c...
#define STR_RES_C__S 320  // c..s
#define STR_RES_C_P_ 321  // c.p.
#define STR_RES_C_PS 322  // c.ps
#define STR_RES_CN__ 323  // cn..
#define STR_RES_CN_S 324  // cn.s
#define STR_RES_CNP_ 325  // cnp.
#define STR_RES_CNPS 326  // cnps
#define STR_RES_SWING 327  // swing
#define STR_RES_SHUFFLE 328  // shuffle
#define STR_RES_PUSH 329  // push
#define STR_RES__LAG 330  // lag
#define STR_RES_HUMAN 331  // human
#define STR_RES_MONKEY 332  // monkey
#define STR_RES_OSCILLATOR_1 333  // oscillator 1
#define STR_RES_OSCILLATOR_2 334  // oscillator 2
#define STR_RES_MIXER 335  // mixer
#define STR_RES_LFO 336  // lfo
#define STR_RES_FILTER_1 337  // filter 1
#define STR_RES_FILTER_2 338  // filter 2
#define STR_RES_ENVELOPE 339  // envelope
#define STR_RES_ARPEGGIATOR 340  // arpeggiator
#define STR_RES_MULTI 341  // multi
#define STR_RES_CLOCK 342  // clock
#define STR_RES_PERFORMANCE 343  // performance
#define STR_RES_SYSTEM 344  // system
#define STR_RES_PT_X_PATCH 345  // pt X patch
#define STR_RES_PT_X_SEQUENCE 346  // pt X sequence
#define STR_RES_PT_X_PROGRAM 347  // pt X program
#define STR_RES_RANDOMIZE 348  // randomize
#define STR_RES_INIT 349  // init
#define STR_RES_PATCH 350  // PATCH
#define STR_RES_SEQUENCE 351  // SEQUENCE
#define STR_RES_PROGRAM 352  // PROGRAM
#define STR_RES__MULTI 353  // MULTI
#define STR_RES____ 354  // ___
#define STR_RES_EQUAL 355  // equal
#define STR_RES_JUST 356  // just
#define STR_RES_PYTHAGOREAN 357  // pythagorean
#define STR_RES_1_4_EB 358  // 1/4 eb
#define STR_RES_1_4_E 359  // 1/4 e
#define STR_RES_1_4_EA 360  // 1/4 ea
#define STR_RES_BHAIRAV 361  // bhairav
#define STR_RES_GUNAKRI 362  // gunakri
#define STR_RES_MARWA 363  // marwa
#define STR_RES_SHREE 364  // shree
#define STR_RES_PURVI 365  // purvi
#define STR_RES_BILAWAL 366  // bilawal
#define STR_RES_YAMAN 367  // yaman
#define STR_RES_KAFI 368  // kafi
#define STR_RES_BHIMPALASREE 369  // bhimpalasree
#define STR_RES_DARBARI 370  // darbari
#define STR_RES_BAGESHREE 371  // bageshree
#define STR_RES_RAGESHREE 372  // rageshree
#define STR_RES_KHAMAJ 373  // khamaj
#define STR_RES_MIMAL 374  // mi'mal
#define STR_RES_PARAMESHWARI 375  // parameshwari
#define STR_RES_RANGESHWARI 376  // rangeshwari
#define STR_RES_GANGESHWARI 377  // gangeshwari
#define STR_RES_KAMESHWARI 378  // kameshwari
#define STR_RES_PA__KAFI 379  // pa. kafi
#define STR_RES_NATBHAIRAV 380  // natbhairav
#define STR_RES_M_KAUNS 381  // m.kauns
#define STR_RES_BAIRAGI 382  // bairagi
#define STR_RES_B_TODI 383  // b.todi
#define STR_RES_CHANDRADEEP 384  // chandradeep
#define STR_RES_KAUSHIK_TODI 385  // kaushik todi
#define STR_RES_JOGESHWARI 386  // jogeshwari
#define STR_RES_RASIA 387  // rasia
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
