<CsoundSynthesizer>
<CsOptions>
-odac7
</CsOptions>
<CsInstruments>

sr 	= 	44100
ksmps 	= 	32
nchnls 	= 	12

giIDs init 100

gkVol[] init giIDs
gkFade[] init giIDs
gkMVol[] init giIDs
gkMFade[] init giIDs
gkStop[] init giIDs 

; Just for testing now!
giThis = 33

gi_osc_handle OSCinit 7777

vbaplsinit 2.01, 12, -150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 140, 180

alwayson "Listener"
alwayson "Outputfilters"

instr Listener
  kID init 0
  kArg1 init 0
  kArg2 init 0
  
next:
	 ; Check for new messages
  kosc_count OSCcount
  if (kosc_count == 0) kgoto end
  printks("kosc_count=%d\n", 1, kosc_count)

  kk OSClisten gi_osc_handle, "/buffer/fadein", "if", kID, kArg1
  if (kk == 1 && kID < giIDs) then
    gkFade[kID] portk 1.0, kArg1	 ;TODO: Must do this with a fader instrument instead!
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/buffer/fadeout", "if", kID, kArg1
  if (kk == 1 && kID < giIDs) then
    gkFade[kID] portk 0.0, kArg1	 ;TODO: Must do this with a fader instrument instead!
    kgoto next
  endif

  kk OSClisten gi_osc_handle, "/stop", "i", kID
  if (kk == 1 && kID < giIDs) then
    gkStop[kID] = 1
    kgoto next
  endif

end:

endin

instr 1
		Sfile	= "C:/Storedal/Lyder/Bredbåndskjerne.wav"
		kreverb init 1.5
		kID init giThis
		String sprintfk "i101 0 1 %d \"%s\" %f", kID, Sfile, kreverb
		ktrig metro 1
		scoreline String, ktrig
		ktrig = 0
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
		
instr 20 ; test global arrays
;		kfade = 0.3
;		kfade port kfade, 2
;		gkFade[giThis] = kfade
endin
		
instr 101
		iID = p4
		iFilLen filelen p5
		p3	= iFilLen + p6
		if (gkStop[iID] < 1) kgoto continue
				turnoff
continue: 
		krel init 0	
		krel release
		if (krel < 1) kgoto cont
			; send OSC message
cont:
		kamp = gkVol[iID] * gkFade[iID] * gkMVol[iID] * gkMFade[iID] ;* 0.5
		ainn soundin p5
		denorm ainn
		a1, a2 reverbsc ainn, -ainn, p6/3, 12000
		aSnd = kamp * ainn ;+ kamp * a2
		kAzim      line       0, p3, -360
		a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12 vbap aSnd, kAzim, 0, 0, 1

		chnmix		a1, "chn_1"
		chnmix		a2, "chn_2"
		chnmix		a3, "chn_3"
		chnmix		a4, "chn_4"
		chnmix		a5, "chn_5"
		chnmix		a6, "chn_6"
		chnmix		a7, "chn_7"
		chnmix		a8, "chn_8"
		chnmix		a9, "chn_9"
		chnmix		a10, "chn_10"
		chnmix		a11, "chn_11"
		chnmix		a12, "chn_12"

endin

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
		
		a12	chnget "chn_12"
		a12 tone a12, iSub
		outch 12, a12
		chnclear "chn_12"

endin

</CsInstruments>

<CsScore>
i 10 0 1
i 1 1 1
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
