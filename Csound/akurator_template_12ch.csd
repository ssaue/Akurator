<CsoundSynthesizer>
<CsOptions>
-odac7
</CsOptions>
<CsInstruments>

sr 	= 	44100
ksmps 	= 	32
nchnls 	= 	12

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
; "Rundt kransen"
vbaplsinit 2.01, 8, -135, -90, -45, 0, 45, 90, 135, 180 
; "Hele skulpturen (simulerer lineær forflytning)"
vbaplsinit 2.02, 12, 0, 20, 40, 60, 80, 100, 120, 140, 160, 180, 200, 220
; "Langs spiret (simulerer lineæar forflytning)"
vbaplsinit 2.03, 3, 0, 45, 90 

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

  kk OSClisten gi_osc_handle, "/play/kulisse", "isf", kID, Sfile, kArg1
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Kulisse\" 0 1 %d \"%s\" %f", kID, Sfile, kArg1
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/play/rekke", "isf", kID, Sfile, kArg1
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Rekke\" 0 1 %d \"%s\" %f", kID, Sfile, kArg1
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/play/signaler", "isf", kID, Sfile, kArg1
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Signaler\" 0 1 %d \"%s\" %f", kID, Sfile, kArg1
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/play/attakker", "isf", kID, Sfile, kArg1
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Attakker\" 0 1 %d \"%s\" %f", kID, Sfile, kArg1
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/play/kaskader", "isf", kID, Sfile, kArg1
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Kaskader\" 0 1 %d \"%s\" %f", kID, Sfile, kArg1
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif
  
  kk OSClisten gi_osc_handle, "/play/rens", "isf", kID, Sfile, kArg1
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Rens\" 0 1 %d \"%s\" %f", kID, Sfile, kArg1
     printks("%s\n", 1, String)
				scoreline String, 1
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/play/dunder", "isf", kID, Sfile, kArg1
  if (kk == 1 && kID < giIDs) then
				String sprintfk "i \"Dunder\" 0 1 %d \"%s\" %f", kID, Sfile, kArg1
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
				istart = gkFade[p4]
    gkFade[p4] linen istart, p3, p5
endin

instr 30 ; volume buffer (abs)
				istart = gkVol[p4]
    gkVol[p4] linen istart, p3, p5
endin

instr 35 ; volume buffer (rel)
				istart = gkVol[p4]
				iend = istart + p5
    gkVol[p4] linen istart, p3, iend
endin

instr 40 ; fade master
				istart = gkMFade[p4]
    gkMFade[p4] linen istart, p3, p5
endin

instr 50 ; volume master (abs)
				istart = gkMVol[p4]
    gkMVol[p4] linen istart, p3, p5
endin

instr 55 ; volume master (rel)
				istart = gkMVol[p4]
				iend = istart + p5
    gkMVol[p4] linen istart, p3, iend
endin

#include "kulisse.inc"		
#include "rekke.inc"
#include "signaler.inc"
#include "attakker.inc"
#include "kaskader.inc"
#include "rens.inc"
#include "dunder.inc"

instr Outputfilters	; Pre-filtering the loudspeakers

		iKrans = 90	; HPF 
		iSpir = 80	; HPF
		iSub = 100	; LPF
		
		a1	chnget "chn_1"
		a1 atone a1, iKrans
		outch 1, a1
		chnclear "chn_1"
		
		a2	chnget "chn_2"
		a2 atone a2, iKrans
		outch 2, a2
		chnclear "chn_2"
		
		a3	chnget "chn_3"
		a3 atone a3, iKrans
		outch 3, a3
		chnclear "chn_3"
		
		a4	chnget "chn_4"
		a4 atone a4, iKrans
		outch 4, a4
		chnclear "chn_4"
		
		a5	chnget "chn_5"
		a5 atone a5, iKrans
		outch 5, a5
		chnclear "chn_5"
		
		a6	chnget "chn_6"
		a6 atone a6, iKrans
		outch 6, a6
		chnclear "chn_6"
		
		a7	chnget "chn_7"
		a7 atone a7, iKrans
		outch 7, a7
		chnclear "chn_7"
		
		a8	chnget "chn_8"
		a8 atone a8, iKrans
		outch 8, a8
		chnclear "chn_8"
		
		a9	chnget "chn_9"
		a9 atone a9, iSpir
		outch 9, a9
		chnclear "chn_9"
		
		a10	chnget "chn_10"
		a10 atone a10, iSpir
		outch 10, a10
		chnclear "chn_10"
		
		a11	chnget "chn_11"
		a11 atone a11, iSpir
		outch 11, a11
		chnclear "chn_11"
		
		a12	chnget "sub"
		a12 tone a12, iSub
		outch 12, a12
		chnclear "sub"

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
 <x>100</x>
 <y>100</y>
 <width>320</width>
 <height>240</height>
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
