instr Hallene_konkret
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
		aSnd soundin p5
		denorm aSnd

		kChannel random 1.0, 3.99
	
		String sprintfk "hall_%d", int(kChannel)
		chnmix		aSnd, String

endin
