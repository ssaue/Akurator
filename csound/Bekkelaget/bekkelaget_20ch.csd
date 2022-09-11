<CsoundSynthesizer>
<CsOptions>
-odac7
</CsOptions>
<CsInstruments>

sr 	= 	44100
ksmps 	= 	32
nchnls 	= 	19

; The number of buffers - this number must be large enough for the project!
giIDs init 30

gkVol[] init giIDs
gkFade[] init giIDs
gkMVol[] init giIDs
gkMFade[] init giIDs
gkStop[] init giIDs 

giOSCreceive init 8010
giOSCsend	   init 9010

gi_osc_handle OSCinit giOSCreceive

; VBAP
; "Tunnel (simulerer line�ar forflytning)"
vbaplsinit 2.01, 0, 25, 50, 75, 100, 125, 150, 175

; "Hall 4 (simulerer line�ar forflytning)"
vbaplsinit 2.02, 5, 0, 22.5, 45, 67.5, 90 

alwayson "Listener"
alwayson "Outputfilters"

instr Listener
  kID init 0
  kArg1 init 0
  kArg2 init 0
  Sfile	= ""
 
next:

	 ; Check for new messages
  kosc_count OSCcount
  if (kosc_count == 0) kgoto end

  kk OSClisten gi_osc_handle, "/play/tunnel_kaskade", "isf", kID, Sfile, kArg1
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Tunnel_kaskade\" 0 1 %d \"%s\" %f", kID, Sfile, kArg1
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/play/tunnel_konkret", "is", kID, Sfile
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Tunnel_konkret\" 0 1 %d \"%s\" ", kID, Sfile
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/play/hall_kaskade", "isf", kID, Sfile, kArg1
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Hall_kaskade\" 0 1 %d \"%s\" %f", kID, Sfile, kArg1
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/play/hall4_konkret", "is", kID, Sfile
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Hall4_konkret\" 0 1 %d \"%s\" ", kID, Sfile
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif
  
  kk OSClisten gi_osc_handle, "/play/hallene_konkret", "is", kID, Sfile
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Hallene_konkret\" 0 1 %d \"%s\" ", kID, Sfile
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/play/draape", "is", kID, Sfile
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Draape\" 0 1 %d \"%s\" ", kID, Sfile
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif
  
  kk OSClisten gi_osc_handle, "/play/kepler", "is", kID, Sfile
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Kepler\" 0 1 %d \"%s\" ", kID, Sfile
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/buffer/fadein", "if", kID, kArg1
  if (kk == 1 && kID < giIDs) then
    event "i", 20, 0, kArg1, kID, 1.0
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/buffer/fadeout", "if", kID, kArg1
  if (kk == 1 && kID < giIDs) then
    event "i", 20, 0, kArg1, kID, 0.0
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/buffer/vol/abs", "if", kID, kArg1, kArg2
  if (kk == 1 && kID < giIDs) then
    event "i", 30, 0, kArg2, kID, kArg1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/buffer/vol/rel", "if", kID, kArg1, kArg2
  if (kk == 1 && kID < giIDs) then
    event "i", 35, 0, kArg2, kID, kArg1
    kgoto next
  endif


  kk OSClisten gi_osc_handle, "/master/fadein", "if", kID, kArg1
  if (kk == 1 && kID < giIDs) then
    event "i", 40, 0, kArg1, kID, 1.0
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/master/fadeout", "if", kID, kArg1
  if (kk == 1 && kID < giIDs) then
    event "i", 40, 0, kArg1, kID, 0.0
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/master/vol/abs", "if", kID, kArg1, kArg2
  if (kk == 1 && kID < giIDs) then
    event "i", 50, 0, kArg2, kID, kArg1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/master/vol/rel", "if", kID, kArg1, kArg2
  if (kk == 1 && kID < giIDs) then
    event "i", 55, 0, kArg2, kID, kArg1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/stop", "i", kID
  if (kk == 1 && kID < giIDs) then
    gkStop[kID] = 1
    kgoto next
  endif

end:

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
i 1 0 3600
i 10 0 1
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
