instr Rekke
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

		irnd = rnd(2)
		istart = irnd > 1 ? 0 : 220	
		iend = irnd > 1 ? 220 : 0
		kAzim      line       istart, p3, iend
		a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12 vbap aSnd, kAzim, 0, 40, 2

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
		chnmix		aSnd+a12, "sub"

endin
