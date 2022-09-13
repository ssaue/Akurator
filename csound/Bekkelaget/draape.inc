instr Draape
		iID = p4
		iFilLen filelen p5
		p3	= iFilLen
		
		iChannel random 1.0, 3.99
		iChannel = int(iChannel)
		
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
		kamp = gkVol[iID] * gkFade[iID] * gkMVol[iID] * gkMFade[iID] * 0.67
		aSnd soundin p5
		denorm aSnd
		
		String sprintfk "drop_%d", iChannel

		chnmix		aSnd, String

endin
