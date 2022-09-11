instr Kepler
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
		kamp = gkVol[iID] * gkFade[iID] * gkMVol[iID] * gkMFade[iID]
		a1,a2 soundin p5
		denorm a1,a2
		a1 = kamp * a1
		a2 = kamp * a2

		chnmix		a1, "drop_1"
		chnmix		a2, "drop_2"
		chnmix		a1, "drop_3"

endin
