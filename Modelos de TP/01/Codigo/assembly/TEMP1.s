f:		sub		sp,sp,24
		sw		ra,16(sp)
		sw		$fp,12(sp)
		sw		gp,8(sp)
		move	$fp,sp
		lw		ra,16(sp)
		addiu	sp,sp,24
		jr		ra