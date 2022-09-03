instr Attakker
		iID = p4
		iFilLen filelen p5
		p3	= iFilLen
		if (gkStop[iID] < 1) kgoto continue
				turnoff

continue: 
		krel init 0	
		krel release
		if (krel < 1) kgoto cont
  		xtratim p6
			 ktrig init 1
			 OSCsend	ktrig, "127.0.0.1", giOSCsend, "/finished", "i", iID
			 ktrig = 0

cont:
		kamp = gkVol[iID] * gkFade[iID] * gkMVol[iID] * gkMFade[iID] * 0.5
		ainn soundin p5
		denorm ainn
		a1, a2 reverbsc ainn, -ainn, p6/3, 12000
		aSnd = kamp * a1 + kamp * a2

		chnmix		aSnd, "chn_1"
		chnmix		aSnd, "chn_2"
		chnmix		aSnd, "chn_3"
		chnmix		aSnd, "chn_4"
		chnmix		aSnd, "chn_5"
		chnmix		aSnd, "chn_6"
		chnmix		aSnd, "chn_7"
		chnmix		aSnd, "chn_8"
		chnmix		aSnd, "chn_9"
		chnmix		aSnd, "chn_10"
		chnmix		aSnd, "chn_11"
		chnmix		aSnd, "sub"

endin
