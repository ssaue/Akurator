<CsoundSynthesizer>
<CsOptions>
-odac
</CsOptions>
<CsInstruments>

sr 	= 	44100
ksmps 	= 	32
nchnls 	= 	2

giIDs init 100

gkVol[] init giIDs
gkFade[] init giIDs
gkMaster[] init giIDs
gkStop[] init giIDs 

giThis = 33


vbaplsinit 2.01, 12, -150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 140, 180

  instr 1
		Sfile	= "C:/Store/Installasjoner/Storedal/Lyder/Bredbåndskjerne.wav"
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
					gkFade[kndx] = 1
					gkMaster[kndx] = 1
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
		krel init 0
		if (gkStop[iID] < 1) kgoto continue
				turnoff
		continue: 
		krel release
		if (krel < 1) kgoto cont
			; send OSC message
		cont:
		kamp = gkVol[iID] * gkFade[iID] * gkMaster[iID] ;* 0.5
ainn soundin p5
denorm ainn
a1, a2 reverbsc ainn, -ainn, p6/3, 12000
aSnd = kamp * ainn ;+ kamp * a2
kAzim      line       0, p3, -360
a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12 vbap aSnd, kAzim, 0, 0, 1
           outch      1, a1, 2, a2
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
