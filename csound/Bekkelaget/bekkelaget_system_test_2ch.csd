<CsoundSynthesizer>
<CsOptions>
-odac1
</CsOptions>
<CsInstruments>

sr 	= 	44100
ksmps 	= 	32
nchnls 	= 	2
0dbfs = 1

vbaplsinit 2.01, 19, 0, 10, 20, 30, 40, 50, 60, 70 ,80, 90, 100, 110, 120, 130, 140, 150, 160, 170 ,180

alwayson "Outputfilters"

instr 10
		Sfile = "C:/Bekkelaget/Lyder/Syntetisk/Normal lang syntetisk/LS1_glasstroll.wav"
		iFilLen filelen Sfile
		ichn filenchnls Sfile	;check number of channels
		iamp = 0.2
		
		iStartChannel = 9
		iEndChannel = 13
		
		loop:
          timout    0, iFilLen, play
          reinit    loop
		play:

;		Mono
;		a1 soundin Sfile
;		denorm a1
;		aSnd = iamp * a1

;		Stereo
		a1,a2 soundin Sfile
		denorm a1,a2
		aSnd = iamp * a1 + iamp * a2

		kAzim      line       iStartChannel*10, iFilLen, iEndChannel*10
		a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19  vbap aSnd, kAzim, 0, 0, 1

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
		chnmix		a13, "chn_13"
		chnmix		a14, "chn_14"
		chnmix		a15, "chn_15"
		chnmix		a16, "chn_16"
		chnmix		a17, "chn_17"
		chnmix		a18, "chn_18"
		chnmix		a19, "chn_19"

endin

instr Outputfilters	; Pre-filtering the loudspeakers

		iDNH = 90	; HPF 
		
		a1	chnget "chn_1"
		a1 atone a1, iDNH
		outch 1, a1
		chnclear "chn_1"
		
		a2	chnget "chn_2"
		a2 atone a2, iDNH
		outch 2, a2
		chnclear "chn_2"
		
		a3	chnget "chn_3"
		a3 atone a3, iDNH
		outch 1, a3
		chnclear "chn_3"
		
		a4	chnget "chn_4"
		a4 atone a4, iDNH
		outch 2, a4
		chnclear "chn_4"
		
		a5	chnget "chn_5"
		a5 atone a5, iDNH
		outch 1, a5
		chnclear "chn_5"
		
		a6	chnget "chn_6"
		a6 atone a6, iDNH
		outch 2, a6
		chnclear "chn_6"
		
		a7	chnget "chn_7"
		a7 atone a7, iDNH
		outch 1, a7
		chnclear "chn_7"
		
		a8	chnget "chn_8"
		a8 atone a8, iDNH
		outch 2, a8
		chnclear "chn_8"
		
		a9	chnget "chn_9"
		a9 atone a9, iDNH
		outch 1, a9
		chnclear "chn_9"
		
		a10	chnget "chn_10"
		a10 atone a10, iDNH
		outch 2, a10
		chnclear "chn_10"
		
		a11	chnget "chn_11"
		a11 atone a11, iDNH
		outch 1, a11
		chnclear "chn_11"
		
		a12	chnget "chn_12"
		a12 tone a12, iDNH
		outch 2, a12
		chnclear "chn_12"

		a13	chnget "chn_13"
		a13 tone a13, iDNH
		outch 1, a13
		chnclear "chn_13"

		a14	chnget "chn_14"
		a14 tone a14, iDNH
		outch 2, a14
		chnclear "chn_14"

		a15	chnget "chn_15"
		a15 tone a15, iDNH
		outch 1, a15
		chnclear "chn_15"

		a16	chnget "chn_16"
		a16 tone a16, iDNH
		outch 2, a16
		chnclear "chn_16"

		a17	chnget "chn_17"
		outch 1, a17
		chnclear "chn_17"

		a18	chnget "chn_18"
		outch 2, a18
		chnclear "chn_18"

		a19	chnget "chn_19"
		outch 1, a19
		chnclear "chn_19"

endin

</CsInstruments>

<CsScore>
i 10 0 3600
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
