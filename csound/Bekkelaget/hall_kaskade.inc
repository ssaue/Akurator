instr Hall_kaskade
		iID = p4
		iFilLen filelen p5
		p3	= iFilLen
		if (gkStop[iID] < 1) kgoto continue
				turnoff

continue: 
		krel init 0	
		krel release
		if (krel < 1) kgoto cont
			 ktrig init 1
			 OSCsend	ktrig, "127.0.0.1", giOSCsend, "/finished", "i", iID
			 ktrig = 0

cont:
		kamp = gkVol[iID] * gkFade[iID] * gkMVol[iID] * gkMFade[iID] * 0.5
		a1,a2 soundin p5
		denorm a1, a2
		aSnd = kamp * a1 + kamp * a2

		kAzim      line       0, p3, 90
		a1, a2, a3, a4, a5  vbap aSnd, kAzim, 0, 0, 2

		chnmix		a1, "hall_1"
		chnmix		a2, "hall_2"
		chnmix		a3, "hall_3"
		chnmix		a4, "hall_4"
		chnmix		a5, "hall_5"

endin
