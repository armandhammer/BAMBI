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
#define STR_RES_OSCILLATOR_1 26  // oscillator 1
#define STR_RES_OSCILLATOR_2 27  // oscillator 2
#define STR_RES_MIXER 28  // mixer
#define STR_RES_LFO 29  // lfo
#define STR_RES_FILTER_1 30  // filter 1
#define STR_RES_FILTER_2 31  // filter 2
#define STR_RES_ENVELOPE 32  // envelope
#define STR_RES_CLOCK 33  // clock
#define STR_RES_SYSTEM 34  // system
#define STR_RES_CRUSH 35  // crush
#define STR_RES_FREQUENCY 36  // frequency
#define STR_RES_ARPEGGIO 37  // arpeggio
#define STR_RES_SEQUENCER 38  // sequencer
#define STR_RES_SPRM 39  // sprm
#define STR_RES_SPREAD_MODE 40  // spread mode
#define STR_RES_STCK 41  // stck
#define STR_RES_CNTR 42  // cntr
#define STR_RES_WIDE 43  // wide
#define STR_RES_SUB 44  // sub-
#define STR_RES_ATTACK 45  // attack
#define STR_RES_DECAY 46  // decay
#define STR_RES_SUSTAIN 47  // sustain
#define STR_RES_RELEASE 48  // release
#define STR_RES_TRIGGER 49  // trigger
#define STR_RES_RATE 50  // rate
#define STR_RES_LFO_EG 51  // lfo/eg
#define STR_RES_VOICE_LFO 52  // voice lfo
#define STR_RES_SOURCE 53  // source
#define STR_RES_DESTINATION 54  // destination
#define STR_RES_IN1 55  // in1
#define STR_RES_IN2 56  // in2
#define STR_RES_MODULATION 57  // modulation
#define STR_RES_MODUL_ 58  // modul.
#define STR_RES__MODULATION 59  // modulation
#define STR_RES_MODIFIER 60  // modifier
#define STR_RES_MODIF_ 61  // modif.
#define STR_RES_VOLUME 62  // volume
#define STR_RES_OCTAVE 63  // octave
#define STR_RES_SPREAD 64  // spread
#define STR_RES_LEGATO 65  // legato
#define STR_RES_PORTAMENTO 66  // portamento
#define STR_RES_ARP_SEQ 67  // arp/seq
#define STR_RES_RAGA 68  // raga
#define STR_RES_DIRECTION 69  // direction
#define STR_RES_PATTERN 70  // pattern
#define STR_RES_CHANNEL 71  // channel
#define STR_RES_PART 72  // part
#define STR_RES_BPM 73  // bpm
#define STR_RES_LTCH 74  // ltch
#define STR_RES_LATCH 75  // latch
#define STR_RES_LOW 76  // low
#define STR_RES_HIGH 77  // high
#define STR_RES_GRID 78  // grid
#define STR_RES_SEQ1_LEN 79  // seq1 len
#define STR_RES_SEQ2_LEN 80  // seq2 len
#define STR_RES_PATT_LEN 81  // patt len
#define STR_RES_LEN1 82  // len1
#define STR_RES_LEN2 83  // len2
#define STR_RES_LENP 84  // lenp
#define STR_RES_GROOVE 85  // groove
#define STR_RES_MIDI 86  // midi
#define STR_RES_SNAP 87  // snap
#define STR_RES_HELP 88  // help
#define STR_RES_AUTO_BACKUP 89  // auto backup
#define STR_RES_LEDS 90  // leds
#define STR_RES_CARD_LEDS 91  // card leds
#define STR_RES_SWAP_COLORS 92  // swap colors
#define STR_RES_INPT_FILTER 93  // inpt filter
#define STR_RES_OUTP_MODE 94  // outp mode
#define STR_RES_EXT 95  // ext
#define STR_RES_OMNI 96  // omni
#define STR_RES_AMNT 97  // amnt
#define STR_RES_SRCE 98  // srce
#define STR_RES_OCT 99  // oct
#define STR_RES_SPRD 100  // sprd
#define STR_RES_A_SQ 101  // a/sq
#define STR_RES_OCTV 102  // octv
#define STR_RES_OFF 103  // off
#define STR_RES_ON 104  // on
#define STR_RES_NONE 105  // none
#define STR_RES_SAW 106  // saw
#define STR_RES_SQUARE 107  // square
#define STR_RES_TRIANGLE 108  // triangle
#define STR_RES_SINE 109  // sine
#define STR_RES_ZSAW 110  // zsaw
#define STR_RES_LPZSAW 111  // lpzsaw
#define STR_RES_PKZSAW 112  // pkzsaw
#define STR_RES_BPZSAW 113  // bpzsaw
#define STR_RES_HPZSAW 114  // hpzsaw
#define STR_RES_LPZPULSE 115  // lpzpulse
#define STR_RES_PKZPULSE 116  // pkzpulse
#define STR_RES_BPZPULSE 117  // bpzpulse
#define STR_RES_HPZPULSE 118  // hpzpulse
#define STR_RES_ZTRIANGLE 119  // ztriangle
#define STR_RES_PAD 120  // pad
#define STR_RES_FM 121  // fm
#define STR_RES_8BITS 122  // 8bits
#define STR_RES_PWM 123  // pwm
#define STR_RES_NOISE 124  // noise
#define STR_RES_VOWEL 125  // vowel
#define STR_RES_MALE 126  // male
#define STR_RES_FEMALE 127  // female
#define STR_RES_CHOIR 128  // choir
#define STR_RES_TAMPURA 129  // tampura
#define STR_RES_BOWED 130  // bowed
#define STR_RES_CELLO 131  // cello
#define STR_RES_VIBES 132  // vibes
#define STR_RES_SLAP 133  // slap
#define STR_RES_EPIANO 134  // epiano
#define STR_RES_ORGAN 135  // organ
#define STR_RES_WAVES 136  // waves
#define STR_RES_DIGITAL 137  // digital
#define STR_RES_DRONE_1 138  // drone 1
#define STR_RES_DRONE_2 139  // drone 2
#define STR_RES_METALLIC 140  // metallic
#define STR_RES_BELL 141  // bell
#define STR_RES_WAVQUENCE 142  // wavquence
#define STR_RES_OLDSAW 143  // oldsaw
#define STR_RES_QPWM 144  // qpwm
#define STR_RES_FMFB 145  // fmfb
#define STR_RES_CSAW 146  // csaw
#define STR_RES_VOWEL_2 147  // vowel 2
#define STR_RES_TRI 148  // tri
#define STR_RES_SQR 149  // sqr
#define STR_RES_S_H 150  // s&h
#define STR_RES_RAMP 151  // ramp
#define STR_RES__SINE 152  // sine
#define STR_RES_HRM2 153  // hrm2
#define STR_RES_HRM3 154  // hrm3
#define STR_RES_HRM5 155  // hrm5
#define STR_RES_GRG1 156  // grg1
#define STR_RES_GRG2 157  // grg2
#define STR_RES_BAT1 158  // bat1
#define STR_RES_BAT2 159  // bat2
#define STR_RES_SPK1 160  // spk1
#define STR_RES_SPK2 161  // spk2
#define STR_RES_LSAW 162  // lsaw
#define STR_RES_LSQR 163  // lsqr
#define STR_RES_RSAW 164  // rsaw
#define STR_RES_RSQR 165  // rsqr
#define STR_RES_STP1 166  // stp1
#define STR_RES_STP2 167  // stp2
#define STR_RES___OFF 168  // off
#define STR_RES_SYNC 169  // sync
#define STR_RES_RINGMOD 170  // ringmod
#define STR_RES_XOR 171  // xor
#define STR_RES_FOLD 172  // fold
#define STR_RES_BITS 173  // bits
#define STR_RES_SQU1 174  // squ1
#define STR_RES_TRI1 175  // tri1
#define STR_RES_PUL1 176  // pul1
#define STR_RES_SQU2 177  // squ2
#define STR_RES_TRI2 178  // tri2
#define STR_RES_PUL2 179  // pul2
#define STR_RES_CLICK 180  // click
#define STR_RES_GLITCH 181  // glitch
#define STR_RES_BLOW 182  // blow
#define STR_RES_METAL 183  // metal
#define STR_RES_POP 184  // pop
#define STR_RES_ENV1 185  // env1
#define STR_RES_ENV2 186  // env2
#define STR_RES_ENV3 187  // env3
#define STR_RES_LFO1 188  // lfo1
#define STR_RES_LFO2 189  // lfo2
#define STR_RES_LFO3 190  // lfo3
#define STR_RES_LFO4 191  // lfo4
#define STR_RES_MOD1 192  // mod1
#define STR_RES_MOD2 193  // mod2
#define STR_RES_MOD3 194  // mod3
#define STR_RES_MOD4 195  // mod4
#define STR_RES_SEQ1 196  // seq1
#define STR_RES_SEQ2 197  // seq2
#define STR_RES_ARP 198  // arp
#define STR_RES_VELO 199  // velo
#define STR_RES_AFTR 200  // aftr
#define STR_RES_BEND 201  // bend
#define STR_RES_MWHL 202  // mwhl
#define STR_RES_WHL2 203  // whl2
#define STR_RES_PDAL 204  // pdal
#define STR_RES_NOTE 205  // note
#define STR_RES_GATE 206  // gate
#define STR_RES_NOIS 207  // nois
#define STR_RES_RAND 208  // rand
#define STR_RES_E256 209  // =256
#define STR_RES_E128 210  // =128
#define STR_RES_E64 211  // =64
#define STR_RES_E32 212  // =32
#define STR_RES_E16 213  // =16
#define STR_RES_E8 214  // =8
#define STR_RES_E4 215  // =4
#define STR_RES_PRM1 216  // prm1
#define STR_RES_PRM2 217  // prm2
#define STR_RES_OSC1 218  // osc1
#define STR_RES_OSC2 219  // osc2
#define STR_RES_31S2 220  // 1+2
#define STR_RES_VIBR 221  // vibr
#define STR_RES_MIX 222  // mix
#define STR_RES_XMOD 223  // xmod
#define STR_RES__NOIS 224  // nois
#define STR_RES__SUB 225  // sub
#define STR_RES_FUZZ 226  // fuzz
#define STR_RES_CRSH 227  // crsh
#define STR_RES_FREQ 228  // freq
#define STR_RES_RESO 229  // reso
#define STR_RES_ATTK 230  // attk
#define STR_RES_DECA 231  // deca
#define STR_RES_RELE 232  // rele
#define STR_RES__LFO4 233  // lfo4
#define STR_RES_VCA 234  // vca
#define STR_RES_ENV_1 235  // env 1
#define STR_RES_ENV_2 236  // env 2
#define STR_RES_ENV_3 237  // env 3
#define STR_RES_LFO_1 238  // lfo 1
#define STR_RES_LFO_2 239  // lfo 2
#define STR_RES_LFO_3 240  // lfo 3
#define STR_RES_LFO_4 241  // lfo 4
#define STR_RES_MOD__1 242  // mod. 1
#define STR_RES_MOD__2 243  // mod. 2
#define STR_RES_MOD__3 244  // mod. 3
#define STR_RES_MOD__4 245  // mod. 4
#define STR_RES_SEQ__1 246  // seq. 1
#define STR_RES_SEQ__2 247  // seq. 2
#define STR_RES__ARP 248  // arp
#define STR_RES__VELO 249  // velo
#define STR_RES_AFTTCH 250  // afttch
#define STR_RES_BENDER 251  // bender
#define STR_RES_MWHEEL 252  // mwheel
#define STR_RES_WHEEL2 253  // wheel2
#define STR_RES_PEDAL 254  // pedal
#define STR_RES__NOTE 255  // note
#define STR_RES__GATE 256  // gate
#define STR_RES__NOISE 257  // noise
#define STR_RES_RANDOM 258  // random
#define STR_RES_E_256 259  // = 256
#define STR_RES_E_32 260  // = 32
#define STR_RES_E_16 261  // = 16
#define STR_RES_E_8 262  // = 8
#define STR_RES_E_4 263  // = 4
#define STR_RES_PARAM_1 264  // param 1
#define STR_RES_PARAM_2 265  // param 2
#define STR_RES_OSC_1 266  // osc 1
#define STR_RES_OSC_2 267  // osc 2
#define STR_RES_OSC_1S2 268  // osc 1+2
#define STR_RES_VIBRATO 269  // vibrato
#define STR_RES__MIX 270  // mix
#define STR_RES__XMOD 271  // xmod
#define STR_RES___NOISE 272  // noise
#define STR_RES_SUBOSC 273  // subosc
#define STR_RES__FUZZ 274  // fuzz
#define STR_RES__CRUSH 275  // crush
#define STR_RES__FREQUENCY 276  // frequency
#define STR_RES__RESO 277  // reso
#define STR_RES__ATTACK 278  // attack
#define STR_RES__DECAY 279  // decay
#define STR_RES__RELEASE 280  // release
#define STR_RES__LFO_4 281  // lfo 4
#define STR_RES__VCA 282  // vca
#define STR_RES_LP 283  // lp
#define STR_RES_BP 284  // bp
#define STR_RES_HP 285  // hp
#define STR_RES_NT 286  // nt
#define STR_RES_FREE 287  // free
#define STR_RES_ENVTLFO 288  // env~lfo
#define STR_RES_LFOTENV 289  // lfo~env
#define STR_RES_STEP_SEQ 290  // step seq
#define STR_RES__ARPEGGIO 291  // arpeggio
#define STR_RES__PATTERN 292  // pattern
#define STR_RES__OFF 293  // off
#define STR_RES_ADD 294  // add
#define STR_RES_PROD 295  // prod
#define STR_RES_ATTN 296  // attn
#define STR_RES_MAX 297  // max
#define STR_RES_MIN 298  // min
#define STR_RES__XOR 299  // xor
#define STR_RES_GE 300  // >=
#define STR_RES_LE 301  // <=
#define STR_RES_QTZ 302  // qtz
#define STR_RES_LAG 303  // lag
#define STR_RES_MONO 304  // mono
#define STR_RES_POLY 305  // poly
#define STR_RES_2X_UNISON 306  // 2x unison
#define STR_RES_CYCLIC 307  // cyclic
#define STR_RES_CHAIN 308  // chain
#define STR_RES_3X_UNISON 309  // 3x unison
#define STR_RES_4X_UNISON 310  // 4x unison
#define STR_RES_OLD 311  // old
#define STR_RES__LOW 312  // low
#define STR_RES__HIGH 313  // high
#define STR_RES__NONE 314  // none
#define STR_RES_UP 315  // up
#define STR_RES_DOWN 316  // down
#define STR_RES_UP_DOWN 317  // up&down
#define STR_RES_PLAYED 318  // played
#define STR_RES__RANDOM 319  // random
#define STR_RES_CHORD 320  // chord
#define STR_RES_1_1 321  // 1/1
#define STR_RES_3_4 322  // 3/4
#define STR_RES_2_3 323  // 2/3
#define STR_RES_1_2 324  // 1/2
#define STR_RES_3_8 325  // 3/8
#define STR_RES_1_3 326  // 1/3
#define STR_RES_1_4 327  // 1/4
#define STR_RES_1_6 328  // 1/6
#define STR_RES_1_8 329  // 1/8
#define STR_RES_1_12 330  // 1/12
#define STR_RES_1_16 331  // 1/16
#define STR_RES_1_24 332  // 1/24
#define STR_RES_1_32 333  // 1/32
#define STR_RES_1_48 334  // 1/48
#define STR_RES_1_96 335  // 1/96
#define STR_RES_THRU 336  // thru
#define STR_RES__SEQUENCER 337  // sequencer
#define STR_RES_CONTROLLR 338  // controllr
#define STR_RES__CHAIN 339  // chain
#define STR_RES_FULL 340  // full
#define STR_RES_____ 341  // ....
#define STR_RES____S 342  // ...s
#define STR_RES___P_ 343  // ..p.
#define STR_RES___PS 344  // ..ps
#define STR_RES__N__ 345  // .n..
#define STR_RES__N_S 346  // .n.s
#define STR_RES__NP_ 347  // .np.
#define STR_RES__NPS 348  // .nps
#define STR_RES_C___ 349  // c...
#define STR_RES_C__S 350  // c..s
#define STR_RES_C_P_ 351  // c.p.
#define STR_RES_C_PS 352  // c.ps
#define STR_RES_CN__ 353  // cn..
#define STR_RES_CN_S 354  // cn.s
#define STR_RES_CNP_ 355  // cnp.
#define STR_RES_CNPS 356  // cnps
#define STR_RES_SWING 357  // swing
#define STR_RES_SHUFFLE 358  // shuffle
#define STR_RES_PUSH 359  // push
#define STR_RES__LAG 360  // lag
#define STR_RES_HUMAN 361  // human
#define STR_RES_MONKEY 362  // monkey
#define STR_RES__OSCILLATOR_1 363  // oscillator 1
#define STR_RES__OSCILLATOR_2 364  // oscillator 2
#define STR_RES__MIXER 365  // mixer
#define STR_RES__LFO 366  // lfo
#define STR_RES__FILTER_1 367  // filter 1
#define STR_RES__FILTER_2 368  // filter 2
#define STR_RES__ENVELOPE 369  // envelope
#define STR_RES_ARPEGGIATOR 370  // arpeggiator
#define STR_RES_MULTI 371  // multi
#define STR_RES__CLOCK 372  // clock
#define STR_RES_PERFORMANCE 373  // performance
#define STR_RES__SYSTEM 374  // system
#define STR_RES_PT_X_PATCH 375  // pt X patch
#define STR_RES_PT_X_SEQUENCE 376  // pt X sequence
#define STR_RES_PT_X_PROGRAM 377  // pt X program
#define STR_RES_RANDOMIZE 378  // randomize
#define STR_RES_INIT 379  // init
#define STR_RES_PATCH 380  // PATCH
#define STR_RES_SEQUENCE 381  // SEQUENCE
#define STR_RES_PROGRAM 382  // PROGRAM
#define STR_RES__MULTI 383  // MULTI
#define STR_RES____ 384  // ___
#define STR_RES_EQUAL 385  // equal
#define STR_RES_JUST 386  // just
#define STR_RES_PYTHAGOREAN 387  // pythagorean
#define STR_RES_1_4_EB 388  // 1/4 eb
#define STR_RES_1_4_E 389  // 1/4 e
#define STR_RES_1_4_EA 390  // 1/4 ea
#define STR_RES_BHAIRAV 391  // bhairav
#define STR_RES_GUNAKRI 392  // gunakri
#define STR_RES_MARWA 393  // marwa
#define STR_RES_SHREE 394  // shree
#define STR_RES_PURVI 395  // purvi
#define STR_RES_BILAWAL 396  // bilawal
#define STR_RES_YAMAN 397  // yaman
#define STR_RES_KAFI 398  // kafi
#define STR_RES_BHIMPALASREE 399  // bhimpalasree
#define STR_RES_DARBARI 400  // darbari
#define STR_RES_BAGESHREE 401  // bageshree
#define STR_RES_RAGESHREE 402  // rageshree
#define STR_RES_KHAMAJ 403  // khamaj
#define STR_RES_MIMAL 404  // mi'mal
#define STR_RES_PARAMESHWARI 405  // parameshwari
#define STR_RES_RANGESHWARI 406  // rangeshwari
#define STR_RES_GANGESHWARI 407  // gangeshwari
#define STR_RES_KAMESHWARI 408  // kameshwari
#define STR_RES_PA__KAFI 409  // pa. kafi
#define STR_RES_NATBHAIRAV 410  // natbhairav
#define STR_RES_M_KAUNS 411  // m.kauns
#define STR_RES_BAIRAGI 412  // bairagi
#define STR_RES_B_TODI 413  // b.todi
#define STR_RES_CHANDRADEEP 414  // chandradeep
#define STR_RES_KAUSHIK_TODI 415  // kaushik todi
#define STR_RES_JOGESHWARI 416  // jogeshwari
#define STR_RES_RASIA 417  // rasia
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
