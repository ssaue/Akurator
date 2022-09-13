<CsoundSynthesizer>
<CsOptions>
-odac6
</CsOptions>
<CsInstruments>

sr 	= 	44100
ksmps 	= 	32
nchnls 	= 	24
0dbfs = 1

; The number of buffers - this number must be large enough for the project!
giIDs init 30

gkVol[] init giIDs
gkFade[] init giIDs
gkMVol[] init giIDs
gkMFade[] init giIDs
gkStop[] init giIDs 

giOSCsend	 init 9001

; VBAP
; "Tunnel (simulerer line�ar forflytning)"
vbaplsinit 2.01, 8, 0, 25, 50, 75, 100, 125, 150, 175

; "Hall 4 (simulerer line�ar forflytning)"
vbaplsinit 2.02, 5, 0, 22.5, 45, 67.5, 90 

alwayson "Outputfilters"

alwayson "Outputfilters"

instr Hall_kaskade_test
	  kTrig init 1
	  Sfile = "C:/Bekkelaget/Lyder/Syntetisk/Normal lang syntetisk/LS1_glasstroll.wav"
	  String sprintfk "i \"Hall_kaskade\" 0 1 %d \"%s\" ", 1, Sfile
     printks("%s\n", 1, String)
	  scoreline String, kTrig
	  kTrig = 0
endin

instr Tunnel_kaskade_test
	  kTrig init 1
	  Sfile = "C:/Bekkelaget/Lyder/Syntetisk/Normal lang syntetisk/LS1_glasstroll.wav"
	  String sprintfk "i \"Tunnel_kaskade\" 0 1 %d \"%s\" ", 1, Sfile
     printks("%s\n", 1, String)
	  scoreline String, kTrig
	  kTrig = 0
endin

instr Tunnel_konkret_test
	  kTrig init 1
	  Sfile = "C:/Bekkelaget/Lyder/Syntetisk/Kort syntetisk/KS2-ringmod2.wav"
	  String sprintfk "i \"Tunnel_konkret\" 0 1 %d \"%s\" ", 1, Sfile
     printks("%s\n", 1, String)
	  scoreline String, kTrig
	  kTrig = 0
endin

instr Hall4_konkret_test
	  kTrig init 1
	  Sfile = "C:/Bekkelaget/Lyder/Konkret/Kort konkret/KK5_urverk.wav"
	  String sprintfk "i \"Hall4_konkret\" 0 1 %d \"%s\" ", 1, Sfile
     printks("%s\n", 1, String)
	  scoreline String, kTrig
	  kTrig = 0
endin

instr Hallene_konkret_test
	  kTrig init 1
	  Sfile = "C:/Bekkelaget/Lyder/Konkret/Lang konkret/LK4_polskmessing.wav"
	  String sprintfk "i \"Hallene_konkret\" 0 1 %d \"%s\" ", 1, Sfile
     printks("%s\n", 1, String)
	  scoreline String, kTrig
	  kTrig = 0
endin

instr Draape_test
	  kTrig init 1
	  Sfile = "C:/Bekkelaget/Lyder/Draape/Normal/BA2.wav"
	  String sprintfk "i \"Draape\" 0 1 %d \"%s\" ", 1, Sfile
     printks("%s\n", 1, String)
	  scoreline String, kTrig
	  kTrig = 0
endin

instr Kepler_test
	  kTrig init 1
	  Sfile = "C:/Bekkelaget/Lyder/Kepler 1.wav"
	  String sprintfk "i \"Kepler\" 0 1 %d \"%s\" ", 1, Sfile
     printks("%s\n", 1, String)
	  scoreline String, kTrig
	  kTrig = 0
endin

instr 10 ;init
		kndx init 0
		until kndx == giIDs do
					gkVol[kndx] = 1
					gkFade[kndx] = 0.3
					gkMVol[kndx] = 1
					gkMFade[kndx] = 1
					gkStop[kndx] = 0
					kndx = kndx+1
		od
		turnoff
endin

instr 20 ; fade buffer
	  kStart = gkFade[p4]
    gkFade[p4] linseg i(kStart), p3, p5
endin

instr 30 ; volume buffer (abs)
	  kStart = gkVol[p4]
    gkVol[p4] linseg i(kStart), p3, p5
endin

instr 35 ; volume buffer (rel)
	  kStart = gkVol[p4]
		iend = i(kStart) + p5
    gkVol[p4] linseg i(kStart), p3, iend
endin

instr 40 ; fade master
	  kStart = gkMFade[p4]
    gkMFade[p4] linseg i(kStart), p3, p5
endin

instr 50 ; volume master (abs)
	  kStart = gkMVol[p4]
    gkMVol[p4] linseg i(kStart), p3, p5
endin

instr 55 ; volume master (rel)
	  kStart = gkMVol[p4]
	  iend = i(kStart) + p5
    gkMVol[p4] linseg i(kStart), p3, iend
endin

#include "tunnel_kaskade.inc"		
#include "tunnel_konkret.inc"
#include "hall_kaskade.inc"
#include "hall4_konkret.inc"
#include "hallene_konkret.inc"
#include "draape.inc"
#include "kepler.inc"

instr Outputfilters	; Pre-filtering the loudspeakers

		iDNH = 90	; HPF 
		
		a1	chnget "tunnel_1"
		a1 atone a1, iDNH
		outch 1, a1
		chnclear "tunnel_1"
		
		a2	chnget "tunnel_2"
		a2 atone a2, iDNH
		outch 2, a2
		chnclear "tunnel_2"
		
		a3	chnget "tunnel_3"
		a3 atone a3, iDNH
		outch 3, a3
		chnclear "tunnel_3"
		
		a4	chnget "tunnel_4"
		a4 atone a4, iDNH
		outch 4, a4
		chnclear "tunnel_4"
		
		a5	chnget "tunnel_5"
		a5 atone a5, iDNH
		outch 5, a5
		chnclear "tunnel_5"
		
		a6	chnget "tunnel_6"
		a6 atone a6, iDNH
		outch 6, a6
		chnclear "tunnel_6"
		
		a7	chnget "tunnel_7"
		a7 atone a7, iDNH
		outch 7, a7
		chnclear "tunnel_7"
		
		a8	chnget "tunnel_8"
		a8 atone a8, iDNH
		outch 8, a8
		chnclear "tunnel_8"
		
		a9	chnget "hall_1"
		a9 atone a9, iDNH
		outch 9, a9
		chnclear "hall_1"
		
		a10	chnget "hall 2"
		a10 atone a10, iDNH
		outch 10, a10
		chnclear "hall_2"
		
		a11	chnget "hall_3"
		a11 atone a11, iDNH
		outch 11, a11
		chnclear "hall_3"
		
		a12	chnget "hall_4"
		a12 tone a12, iDNH
		outch 12, a12
		chnclear "hall_4"

		a13	chnget "hall_5"
		a13 tone a13, iDNH
		outch 13, a13
		chnclear "hall_5"

		a14	chnget "hall_6"
		a14 tone a14, iDNH
		outch 14, a14
		chnclear "hall_6"

		a15	chnget "hall_7"
		a15 tone a15, iDNH
		outch 15, a15
		chnclear "hall_7"

		a16	chnget "hall_8"
		a16 tone a16, iDNH
		outch 16, a16
		chnclear "hall_8"

; No filtering on the large loudspeakers in hall 4
		a17	chnget "drop_1"
		outch 17, a17
		chnclear "drop_1"

		a18	chnget "drop_2"
		outch 18, a18
		chnclear "drop_2"

		a19	chnget "drop_3"
		outch 19, a19
		chnclear "drop_3"

endin

</CsInstruments>

<CsScore>
i 10 0 1
i "Kepler_test" 1 1
;i "Draape_test" 1 1
;i "Hall_kaskade_test" 1 1
;i "Tunnel_kaskade_test" 1 1
;i "Tunnel_konkret_test" 1 1
;i "Hall4_konkret_test" 1 1
;i "Hallene_konkret_test" 1 1
f 0 z ; run "forever"
e
</CsScore>
</CsoundSynthesizer>
<bsbPanel>
 <label>Widgets</label>
 <objectName/>
 <x>0</x>
 <y>0</y>
 <width>0</width>
 <height>0</height>
 <visible>true</visible>
 <uuid/>
 <bgcolor mode="nobackground">
  <r>255</r>
  <g>255</g>
  <b>255</b>
 </bgcolor>
</bsbPanel>
<bsbPresets>
</bsbPresets>
