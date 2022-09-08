instr Tunnel_kaskade
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

		kAzim      line       0, p3, 90
		a1, a2, a3, a4, a5, a6, a7, a8  vbap aSnd, kAzim, 0, 0, 2

		chnmix		a1, "hall_4"
		chnmix		a2, "hall_5"
		chnmix		a3, "hall_6"
		chnmix		a4, "hall_7"
		chnmix		a5, "hall_8"

endin
