
bomb:     file format elf32-i386


Disassembly of section .init:

080486a4 <_init>:
 80486a4:	53                   	push   %ebx
 80486a5:	83 ec 08             	sub    $0x8,%esp
 80486a8:	e8 23 02 00 00       	call   80488d0 <__x86.get_pc_thunk.bx>
 80486ad:	81 c3 4b 2a 00 00    	add    $0x2a4b,%ebx
 80486b3:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 80486b9:	85 c0                	test   %eax,%eax
 80486bb:	74 05                	je     80486c2 <_init+0x1e>
 80486bd:	e8 de 00 00 00       	call   80487a0 <__gmon_start__@plt>
 80486c2:	83 c4 08             	add    $0x8,%esp
 80486c5:	5b                   	pop    %ebx
 80486c6:	c3                   	ret    

Disassembly of section .plt:

080486d0 <read@plt-0x10>:
 80486d0:	ff 35 fc b0 04 08    	pushl  0x804b0fc
 80486d6:	ff 25 00 b1 04 08    	jmp    *0x804b100
 80486dc:	00 00                	add    %al,(%eax)
	...

080486e0 <read@plt>:
 80486e0:	ff 25 04 b1 04 08    	jmp    *0x804b104
 80486e6:	68 00 00 00 00       	push   $0x0
 80486eb:	e9 e0 ff ff ff       	jmp    80486d0 <_init+0x2c>

080486f0 <printf@plt>:
 80486f0:	ff 25 08 b1 04 08    	jmp    *0x804b108
 80486f6:	68 08 00 00 00       	push   $0x8
 80486fb:	e9 d0 ff ff ff       	jmp    80486d0 <_init+0x2c>

08048700 <fflush@plt>:
 8048700:	ff 25 0c b1 04 08    	jmp    *0x804b10c
 8048706:	68 10 00 00 00       	push   $0x10
 804870b:	e9 c0 ff ff ff       	jmp    80486d0 <_init+0x2c>

08048710 <fgets@plt>:
 8048710:	ff 25 10 b1 04 08    	jmp    *0x804b110
 8048716:	68 18 00 00 00       	push   $0x18
 804871b:	e9 b0 ff ff ff       	jmp    80486d0 <_init+0x2c>

08048720 <signal@plt>:
 8048720:	ff 25 14 b1 04 08    	jmp    *0x804b114
 8048726:	68 20 00 00 00       	push   $0x20
 804872b:	e9 a0 ff ff ff       	jmp    80486d0 <_init+0x2c>

08048730 <sleep@plt>:
 8048730:	ff 25 18 b1 04 08    	jmp    *0x804b118
 8048736:	68 28 00 00 00       	push   $0x28
 804873b:	e9 90 ff ff ff       	jmp    80486d0 <_init+0x2c>

08048740 <alarm@plt>:
 8048740:	ff 25 1c b1 04 08    	jmp    *0x804b11c
 8048746:	68 30 00 00 00       	push   $0x30
 804874b:	e9 80 ff ff ff       	jmp    80486d0 <_init+0x2c>

08048750 <bcopy@plt>:
 8048750:	ff 25 20 b1 04 08    	jmp    *0x804b120
 8048756:	68 38 00 00 00       	push   $0x38
 804875b:	e9 70 ff ff ff       	jmp    80486d0 <_init+0x2c>

08048760 <strcpy@plt>:
 8048760:	ff 25 24 b1 04 08    	jmp    *0x804b124
 8048766:	68 40 00 00 00       	push   $0x40
 804876b:	e9 60 ff ff ff       	jmp    80486d0 <_init+0x2c>

08048770 <gethostname@plt>:
 8048770:	ff 25 28 b1 04 08    	jmp    *0x804b128
 8048776:	68 48 00 00 00       	push   $0x48
 804877b:	e9 50 ff ff ff       	jmp    80486d0 <_init+0x2c>

08048780 <getenv@plt>:
 8048780:	ff 25 2c b1 04 08    	jmp    *0x804b12c
 8048786:	68 50 00 00 00       	push   $0x50
 804878b:	e9 40 ff ff ff       	jmp    80486d0 <_init+0x2c>

08048790 <puts@plt>:
 8048790:	ff 25 30 b1 04 08    	jmp    *0x804b130
 8048796:	68 58 00 00 00       	push   $0x58
 804879b:	e9 30 ff ff ff       	jmp    80486d0 <_init+0x2c>

080487a0 <__gmon_start__@plt>:
 80487a0:	ff 25 34 b1 04 08    	jmp    *0x804b134
 80487a6:	68 60 00 00 00       	push   $0x60
 80487ab:	e9 20 ff ff ff       	jmp    80486d0 <_init+0x2c>

080487b0 <exit@plt>:
 80487b0:	ff 25 38 b1 04 08    	jmp    *0x804b138
 80487b6:	68 68 00 00 00       	push   $0x68
 80487bb:	e9 10 ff ff ff       	jmp    80486d0 <_init+0x2c>

080487c0 <__libc_start_main@plt>:
 80487c0:	ff 25 3c b1 04 08    	jmp    *0x804b13c
 80487c6:	68 70 00 00 00       	push   $0x70
 80487cb:	e9 00 ff ff ff       	jmp    80486d0 <_init+0x2c>

080487d0 <fprintf@plt>:
 80487d0:	ff 25 40 b1 04 08    	jmp    *0x804b140
 80487d6:	68 78 00 00 00       	push   $0x78
 80487db:	e9 f0 fe ff ff       	jmp    80486d0 <_init+0x2c>

080487e0 <write@plt>:
 80487e0:	ff 25 44 b1 04 08    	jmp    *0x804b144
 80487e6:	68 80 00 00 00       	push   $0x80
 80487eb:	e9 e0 fe ff ff       	jmp    80486d0 <_init+0x2c>

080487f0 <strcasecmp@plt>:
 80487f0:	ff 25 48 b1 04 08    	jmp    *0x804b148
 80487f6:	68 88 00 00 00       	push   $0x88
 80487fb:	e9 d0 fe ff ff       	jmp    80486d0 <_init+0x2c>

08048800 <__isoc99_sscanf@plt>:
 8048800:	ff 25 4c b1 04 08    	jmp    *0x804b14c
 8048806:	68 90 00 00 00       	push   $0x90
 804880b:	e9 c0 fe ff ff       	jmp    80486d0 <_init+0x2c>

08048810 <fopen@plt>:
 8048810:	ff 25 50 b1 04 08    	jmp    *0x804b150
 8048816:	68 98 00 00 00       	push   $0x98
 804881b:	e9 b0 fe ff ff       	jmp    80486d0 <_init+0x2c>

08048820 <__errno_location@plt>:
 8048820:	ff 25 54 b1 04 08    	jmp    *0x804b154
 8048826:	68 a0 00 00 00       	push   $0xa0
 804882b:	e9 a0 fe ff ff       	jmp    80486d0 <_init+0x2c>

08048830 <sprintf@plt>:
 8048830:	ff 25 58 b1 04 08    	jmp    *0x804b158
 8048836:	68 a8 00 00 00       	push   $0xa8
 804883b:	e9 90 fe ff ff       	jmp    80486d0 <_init+0x2c>

08048840 <socket@plt>:
 8048840:	ff 25 5c b1 04 08    	jmp    *0x804b15c
 8048846:	68 b0 00 00 00       	push   $0xb0
 804884b:	e9 80 fe ff ff       	jmp    80486d0 <_init+0x2c>

08048850 <gethostbyname@plt>:
 8048850:	ff 25 60 b1 04 08    	jmp    *0x804b160
 8048856:	68 b8 00 00 00       	push   $0xb8
 804885b:	e9 70 fe ff ff       	jmp    80486d0 <_init+0x2c>

08048860 <strtol@plt>:
 8048860:	ff 25 64 b1 04 08    	jmp    *0x804b164
 8048866:	68 c0 00 00 00       	push   $0xc0
 804886b:	e9 60 fe ff ff       	jmp    80486d0 <_init+0x2c>

08048870 <connect@plt>:
 8048870:	ff 25 68 b1 04 08    	jmp    *0x804b168
 8048876:	68 c8 00 00 00       	push   $0xc8
 804887b:	e9 50 fe ff ff       	jmp    80486d0 <_init+0x2c>

08048880 <close@plt>:
 8048880:	ff 25 6c b1 04 08    	jmp    *0x804b16c
 8048886:	68 d0 00 00 00       	push   $0xd0
 804888b:	e9 40 fe ff ff       	jmp    80486d0 <_init+0x2c>

08048890 <__ctype_b_loc@plt>:
 8048890:	ff 25 70 b1 04 08    	jmp    *0x804b170
 8048896:	68 d8 00 00 00       	push   $0xd8
 804889b:	e9 30 fe ff ff       	jmp    80486d0 <_init+0x2c>

Disassembly of section .text:

080488a0 <_start>:
 80488a0:	31 ed                	xor    %ebp,%ebp
 80488a2:	5e                   	pop    %esi
 80488a3:	89 e1                	mov    %esp,%ecx
 80488a5:	83 e4 f0             	and    $0xfffffff0,%esp
 80488a8:	50                   	push   %eax
 80488a9:	54                   	push   %esp
 80488aa:	52                   	push   %edx
 80488ab:	68 20 9f 04 08       	push   $0x8049f20
 80488b0:	68 c0 9e 04 08       	push   $0x8049ec0
 80488b5:	51                   	push   %ecx
 80488b6:	56                   	push   %esi
 80488b7:	68 9b 89 04 08       	push   $0x804899b
 80488bc:	e8 ff fe ff ff       	call   80487c0 <__libc_start_main@plt>
 80488c1:	f4                   	hlt    
 80488c2:	66 90                	xchg   %ax,%ax
 80488c4:	66 90                	xchg   %ax,%ax
 80488c6:	66 90                	xchg   %ax,%ax
 80488c8:	66 90                	xchg   %ax,%ax
 80488ca:	66 90                	xchg   %ax,%ax
 80488cc:	66 90                	xchg   %ax,%ax
 80488ce:	66 90                	xchg   %ax,%ax

080488d0 <__x86.get_pc_thunk.bx>:
 80488d0:	8b 1c 24             	mov    (%esp),%ebx
 80488d3:	c3                   	ret    
 80488d4:	66 90                	xchg   %ax,%ax
 80488d6:	66 90                	xchg   %ax,%ax
 80488d8:	66 90                	xchg   %ax,%ax
 80488da:	66 90                	xchg   %ax,%ax
 80488dc:	66 90                	xchg   %ax,%ax
 80488de:	66 90                	xchg   %ax,%ax

080488e0 <deregister_tm_clones>:
 80488e0:	b8 c3 b8 04 08       	mov    $0x804b8c3,%eax
 80488e5:	2d c0 b8 04 08       	sub    $0x804b8c0,%eax
 80488ea:	83 f8 06             	cmp    $0x6,%eax
 80488ed:	76 1a                	jbe    8048909 <deregister_tm_clones+0x29>
 80488ef:	b8 00 00 00 00       	mov    $0x0,%eax
 80488f4:	85 c0                	test   %eax,%eax
 80488f6:	74 11                	je     8048909 <deregister_tm_clones+0x29>
 80488f8:	55                   	push   %ebp
 80488f9:	89 e5                	mov    %esp,%ebp
 80488fb:	83 ec 14             	sub    $0x14,%esp
 80488fe:	68 c0 b8 04 08       	push   $0x804b8c0
 8048903:	ff d0                	call   *%eax
 8048905:	83 c4 10             	add    $0x10,%esp
 8048908:	c9                   	leave  
 8048909:	f3 c3                	repz ret 
 804890b:	90                   	nop
 804890c:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi

08048910 <register_tm_clones>:
 8048910:	b8 c0 b8 04 08       	mov    $0x804b8c0,%eax
 8048915:	2d c0 b8 04 08       	sub    $0x804b8c0,%eax
 804891a:	c1 f8 02             	sar    $0x2,%eax
 804891d:	89 c2                	mov    %eax,%edx
 804891f:	c1 ea 1f             	shr    $0x1f,%edx
 8048922:	01 d0                	add    %edx,%eax
 8048924:	d1 f8                	sar    %eax
 8048926:	74 1b                	je     8048943 <register_tm_clones+0x33>
 8048928:	ba 00 00 00 00       	mov    $0x0,%edx
 804892d:	85 d2                	test   %edx,%edx
 804892f:	74 12                	je     8048943 <register_tm_clones+0x33>
 8048931:	55                   	push   %ebp
 8048932:	89 e5                	mov    %esp,%ebp
 8048934:	83 ec 10             	sub    $0x10,%esp
 8048937:	50                   	push   %eax
 8048938:	68 c0 b8 04 08       	push   $0x804b8c0
 804893d:	ff d2                	call   *%edx
 804893f:	83 c4 10             	add    $0x10,%esp
 8048942:	c9                   	leave  
 8048943:	f3 c3                	repz ret 
 8048945:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048949:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048950 <__do_global_dtors_aux>:
 8048950:	80 3d e8 b8 04 08 00 	cmpb   $0x0,0x804b8e8
 8048957:	75 13                	jne    804896c <__do_global_dtors_aux+0x1c>
 8048959:	55                   	push   %ebp
 804895a:	89 e5                	mov    %esp,%ebp
 804895c:	83 ec 08             	sub    $0x8,%esp
 804895f:	e8 7c ff ff ff       	call   80488e0 <deregister_tm_clones>
 8048964:	c6 05 e8 b8 04 08 01 	movb   $0x1,0x804b8e8
 804896b:	c9                   	leave  
 804896c:	f3 c3                	repz ret 
 804896e:	66 90                	xchg   %ax,%ax

08048970 <frame_dummy>:
 8048970:	b8 08 b0 04 08       	mov    $0x804b008,%eax
 8048975:	8b 10                	mov    (%eax),%edx
 8048977:	85 d2                	test   %edx,%edx
 8048979:	75 05                	jne    8048980 <frame_dummy+0x10>
 804897b:	eb 93                	jmp    8048910 <register_tm_clones>
 804897d:	8d 76 00             	lea    0x0(%esi),%esi
 8048980:	ba 00 00 00 00       	mov    $0x0,%edx
 8048985:	85 d2                	test   %edx,%edx
 8048987:	74 f2                	je     804897b <frame_dummy+0xb>
 8048989:	55                   	push   %ebp
 804898a:	89 e5                	mov    %esp,%ebp
 804898c:	83 ec 14             	sub    $0x14,%esp
 804898f:	50                   	push   %eax
 8048990:	ff d2                	call   *%edx
 8048992:	83 c4 10             	add    $0x10,%esp
 8048995:	c9                   	leave  
 8048996:	e9 75 ff ff ff       	jmp    8048910 <register_tm_clones>

/************************************************************************/

0804899b <main>:
 804899b:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 804899f:	83 e4 f0             	and    $0xfffffff0,%esp
 80489a2:	ff 71 fc             	pushl  -0x4(%ecx)
 80489a5:	55                   	push   %ebp
 80489a6:	89 e5                	mov    %esp,%ebp
 80489a8:	53                   	push   %ebx
 80489a9:	51                   	push   %ecx
 80489aa:	8b 01                	mov    (%ecx),%eax
 80489ac:	8b 59 04             	mov    0x4(%ecx),%ebx
 80489af:	83 f8 01             	cmp    $0x1,%eax
 80489b2:	75 0c                	jne    80489c0 <main+0x25>
 80489b4:	a1 e0 b8 04 08       	mov    0x804b8e0,%eax
 80489b9:	a3 f0 b8 04 08       	mov    %eax,0x804b8f0
 80489be:	eb 5a                	jmp    8048a1a <main+0x7f>
 80489c0:	83 f8 02             	cmp    $0x2,%eax
 80489c3:	75 3a                	jne    80489ff <main+0x64>
 80489c5:	83 ec 08             	sub    $0x8,%esp
 80489c8:	68 eb a3 04 08       	push   $0x804a3eb
 80489cd:	ff 73 04             	pushl  0x4(%ebx)
 80489d0:	e8 3b fe ff ff       	call   8048810 <fopen@plt>
 80489d5:	a3 f0 b8 04 08       	mov    %eax,0x804b8f0
 80489da:	83 c4 10             	add    $0x10,%esp
 80489dd:	85 c0                	test   %eax,%eax
 80489df:	75 39                	jne    8048a1a <main+0x7f>
 80489e1:	83 ec 04             	sub    $0x4,%esp
 80489e4:	ff 73 04             	pushl  0x4(%ebx)
 80489e7:	ff 33                	pushl  (%ebx)
 80489e9:	68 40 9f 04 08       	push   $0x8049f40
 80489ee:	e8 fd fc ff ff       	call   80486f0 <printf@plt>
 80489f3:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 80489fa:	e8 b1 fd ff ff       	call   80487b0 <exit@plt>
 80489ff:	83 ec 08             	sub    $0x8,%esp
 8048a02:	ff 33                	pushl  (%ebx)
 8048a04:	68 5d 9f 04 08       	push   $0x8049f5d
 8048a09:	e8 e2 fc ff ff       	call   80486f0 <printf@plt>
 8048a0e:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048a15:	e8 96 fd ff ff       	call   80487b0 <exit@plt>
 8048a1a:	e8 66 05 00 00       	call   8048f85 <initialize_bomb>
 8048a1f:	83 ec 0c             	sub    $0xc,%esp
 8048a22:	68 c4 9f 04 08       	push   $0x8049fc4
 8048a27:	e8 64 fd ff ff       	call   8048790 <puts@plt>
 8048a2c:	c7 04 24 00 a0 04 08 	movl   $0x804a000,(%esp)
 8048a33:	e8 58 fd ff ff       	call   8048790 <puts@plt>
 8048a38:	e8 c9 07 00 00       	call   8049206 <read_line>
 8048a3d:	89 04 24             	mov    %eax,(%esp)
 8048a40:	e8 ad 00 00 00       	call   8048af2 <phase_1>
 8048a45:	e8 b5 08 00 00       	call   80492ff <phase_defused>
 8048a4a:	c7 04 24 2c a0 04 08 	movl   $0x804a02c,(%esp)
 8048a51:	e8 3a fd ff ff       	call   8048790 <puts@plt>
 8048a56:	e8 ab 07 00 00       	call   8049206 <read_line>
 8048a5b:	89 04 24             	mov    %eax,(%esp)
 8048a5e:	e8 b0 00 00 00       	call   8048b13 <phase_2>
 8048a63:	e8 97 08 00 00       	call   80492ff <phase_defused>
 8048a68:	c7 04 24 77 9f 04 08 	movl   $0x8049f77,(%esp)
 8048a6f:	e8 1c fd ff ff       	call   8048790 <puts@plt>
 8048a74:	e8 8d 07 00 00       	call   8049206 <read_line>
 8048a79:	89 04 24             	mov    %eax,(%esp)
 8048a7c:	e8 df 00 00 00       	call   8048b60 <phase_3>
 8048a81:	e8 79 08 00 00       	call   80492ff <phase_defused>
 8048a86:	c7 04 24 95 9f 04 08 	movl   $0x8049f95,(%esp)
 8048a8d:	e8 fe fc ff ff       	call   8048790 <puts@plt>
 8048a92:	e8 6f 07 00 00       	call   8049206 <read_line>
 8048a97:	89 04 24             	mov    %eax,(%esp)
 8048a9a:	e8 aa 01 00 00       	call   8048c49 <phase_4>
 8048a9f:	e8 5b 08 00 00       	call   80492ff <phase_defused>
 8048aa4:	c7 04 24 58 a0 04 08 	movl   $0x804a058,(%esp)
 8048aab:	e8 e0 fc ff ff       	call   8048790 <puts@plt>
 8048ab0:	e8 51 07 00 00       	call   8049206 <read_line>
 8048ab5:	89 04 24             	mov    %eax,(%esp)
 8048ab8:	e8 e3 01 00 00       	call   8048ca0 <phase_5>
 8048abd:	e8 3d 08 00 00       	call   80492ff <phase_defused>
 8048ac2:	c7 04 24 a4 9f 04 08 	movl   $0x8049fa4,(%esp)
 8048ac9:	e8 c2 fc ff ff       	call   8048790 <puts@plt>
 8048ace:	e8 33 07 00 00       	call   8049206 <read_line>
 8048ad3:	89 04 24             	mov    %eax,(%esp)
 8048ad6:	e8 27 02 00 00       	call   8048d02 <phase_6>
 8048adb:	e8 1f 08 00 00       	call   80492ff <phase_defused>
 8048ae0:	83 c4 10             	add    $0x10,%esp
 8048ae3:	b8 00 00 00 00       	mov    $0x0,%eax
 8048ae8:	8d 65 f8             	lea    -0x8(%ebp),%esp
 8048aeb:	59                   	pop    %ecx
 8048aec:	5b                   	pop    %ebx
 8048aed:	5d                   	pop    %ebp
 8048aee:	8d 61 fc             	lea    -0x4(%ecx),%esp
 8048af1:	c3                   	ret    

08048af2 <phase_1>:
 8048af2:	83 ec 14             	sub    $0x14,%esp
 8048af5:	68 7c a0 04 08       	push   $0x804a07c
 8048afa:	ff 74 24 1c          	pushl  0x1c(%esp)
 8048afe:	e8 1d 04 00 00       	call   8048f20 <strings_not_equal>
 8048b03:	83 c4 10             	add    $0x10,%esp
 8048b06:	85 c0                	test   %eax,%eax
 8048b08:	74 05                	je     8048b0f <phase_1+0x1d>
 8048b0a:	e8 7f 06 00 00       	call   804918e <explode_bomb>
 8048b0f:	83 c4 0c             	add    $0xc,%esp
 8048b12:	c3                   	ret    

08048b13 <phase_2>:
 8048b13:	56                   	push   %esi
 8048b14:	53                   	push   %ebx
 8048b15:	83 ec 2c             	sub    $0x2c,%esp
 8048b18:	8d 44 24 10          	lea    0x10(%esp),%eax
 8048b1c:	50                   	push   %eax
 8048b1d:	ff 74 24 3c          	pushl  0x3c(%esp)
 8048b21:	e8 a5 06 00 00       	call   80491cb <read_six_numbers>
 8048b26:	83 c4 10             	add    $0x10,%esp
 8048b29:	83 7c 24 08 00       	cmpl   $0x0,0x8(%esp)
 8048b2e:	75 07                	jne    8048b37 <phase_2+0x24>
 8048b30:	83 7c 24 0c 01       	cmpl   $0x1,0xc(%esp)
 8048b35:	74 05                	je     8048b3c <phase_2+0x29>
 8048b37:	e8 52 06 00 00       	call   804918e <explode_bomb>
 8048b3c:	8d 5c 24 08          	lea    0x8(%esp),%ebx
 8048b40:	8d 74 24 18          	lea    0x18(%esp),%esi
 8048b44:	8b 43 04             	mov    0x4(%ebx),%eax
 8048b47:	03 03                	add    (%ebx),%eax
 8048b49:	39 43 08             	cmp    %eax,0x8(%ebx)
 8048b4c:	74 05                	je     8048b53 <phase_2+0x40>
 8048b4e:	e8 3b 06 00 00       	call   804918e <explode_bomb>
 8048b53:	83 c3 04             	add    $0x4,%ebx
 8048b56:	39 f3                	cmp    %esi,%ebx
 8048b58:	75 ea                	jne    8048b44 <phase_2+0x31>
 8048b5a:	83 c4 24             	add    $0x24,%esp
 8048b5d:	5b                   	pop    %ebx
 8048b5e:	5e                   	pop    %esi
 8048b5f:	c3                   	ret    

08048b60 <phase_3>:
 8048b60:	83 ec 1c             	sub    $0x1c,%esp
 8048b63:	8d 44 24 08          	lea    0x8(%esp),%eax
 8048b67:	50                   	push   %eax
 8048b68:	8d 44 24 10          	lea    0x10(%esp),%eax
 8048b6c:	50                   	push   %eax
 8048b6d:	68 4d a3 04 08       	push   $0x804a34d
 8048b72:	ff 74 24 2c          	pushl  0x2c(%esp)
 8048b76:	e8 85 fc ff ff       	call   8048800 <__isoc99_sscanf@plt>
 8048b7b:	83 c4 10             	add    $0x10,%esp
 8048b7e:	83 f8 01             	cmp    $0x1,%eax
 8048b81:	7f 05                	jg     8048b88 <phase_3+0x28>
 8048b83:	e8 06 06 00 00       	call   804918e <explode_bomb>
 8048b88:	83 7c 24 0c 07       	cmpl   $0x7,0xc(%esp)
 8048b8d:	77 3c                	ja     8048bcb <phase_3+0x6b>
 8048b8f:	8b 44 24 0c          	mov    0xc(%esp),%eax
 8048b93:	ff 24 85 dc a0 04 08 	jmp    *0x804a0dc(,%eax,4)
 8048b9a:	b8 c9 01 00 00       	mov    $0x1c9,%eax
 8048b9f:	eb 3b                	jmp    8048bdc <phase_3+0x7c>
 8048ba1:	b8 7f 03 00 00       	mov    $0x37f,%eax
 8048ba6:	eb 34                	jmp    8048bdc <phase_3+0x7c>
 8048ba8:	b8 c0 01 00 00       	mov    $0x1c0,%eax
 8048bad:	eb 2d                	jmp    8048bdc <phase_3+0x7c>
 8048baf:	b8 a2 01 00 00       	mov    $0x1a2,%eax
 8048bb4:	eb 26                	jmp    8048bdc <phase_3+0x7c>
 8048bb6:	b8 57 02 00 00       	mov    $0x257,%eax
 8048bbb:	eb 1f                	jmp    8048bdc <phase_3+0x7c>
 8048bbd:	b8 44 02 00 00       	mov    $0x244,%eax
 8048bc2:	eb 18                	jmp    8048bdc <phase_3+0x7c>
 8048bc4:	b8 43 03 00 00       	mov    $0x343,%eax
 8048bc9:	eb 11                	jmp    8048bdc <phase_3+0x7c>
 8048bcb:	e8 be 05 00 00       	call   804918e <explode_bomb>
 8048bd0:	b8 00 00 00 00       	mov    $0x0,%eax
 8048bd5:	eb 05                	jmp    8048bdc <phase_3+0x7c>
 8048bd7:	b8 28 02 00 00       	mov    $0x228,%eax
 8048bdc:	3b 44 24 08          	cmp    0x8(%esp),%eax
 8048be0:	74 05                	je     8048be7 <phase_3+0x87>
 8048be2:	e8 a7 05 00 00       	call   804918e <explode_bomb>
 8048be7:	83 c4 1c             	add    $0x1c,%esp
 8048bea:	c3                   	ret    

08048beb <func4>:
 8048beb:	56                   	push   %esi
 8048bec:	53                   	push   %ebx
 8048bed:	83 ec 04             	sub    $0x4,%esp
 8048bf0:	8b 4c 24 10          	mov    0x10(%esp),%ecx
 8048bf4:	8b 5c 24 14          	mov    0x14(%esp),%ebx
 8048bf8:	8b 74 24 18          	mov    0x18(%esp),%esi
 8048bfc:	89 f0                	mov    %esi,%eax
 8048bfe:	29 d8                	sub    %ebx,%eax
 8048c00:	89 c2                	mov    %eax,%edx
 8048c02:	c1 ea 1f             	shr    $0x1f,%edx
 8048c05:	01 d0                	add    %edx,%eax
 8048c07:	d1 f8                	sar    %eax
 8048c09:	8d 14 18             	lea    (%eax,%ebx,1),%edx
 8048c0c:	39 ca                	cmp    %ecx,%edx
 8048c0e:	7e 15                	jle    8048c25 <func4+0x3a>
 8048c10:	83 ec 04             	sub    $0x4,%esp
 8048c13:	83 ea 01             	sub    $0x1,%edx
 8048c16:	52                   	push   %edx
 8048c17:	53                   	push   %ebx
 8048c18:	51                   	push   %ecx
 8048c19:	e8 cd ff ff ff       	call   8048beb <func4>
 8048c1e:	83 c4 10             	add    $0x10,%esp
 8048c21:	01 c0                	add    %eax,%eax
 8048c23:	eb 1e                	jmp    8048c43 <func4+0x58>
 8048c25:	b8 00 00 00 00       	mov    $0x0,%eax
 8048c2a:	39 ca                	cmp    %ecx,%edx
 8048c2c:	7d 15                	jge    8048c43 <func4+0x58>
 8048c2e:	83 ec 04             	sub    $0x4,%esp
 8048c31:	56                   	push   %esi
 8048c32:	83 c2 01             	add    $0x1,%edx
 8048c35:	52                   	push   %edx
 8048c36:	51                   	push   %ecx
 8048c37:	e8 af ff ff ff       	call   8048beb <func4>
 8048c3c:	83 c4 10             	add    $0x10,%esp
 8048c3f:	8d 44 00 01          	lea    0x1(%eax,%eax,1),%eax
 8048c43:	83 c4 04             	add    $0x4,%esp
 8048c46:	5b                   	pop    %ebx
 8048c47:	5e                   	pop    %esi
 8048c48:	c3                   	ret    

08048c49 <phase_4>:
 8048c49:	83 ec 1c             	sub    $0x1c,%esp
 8048c4c:	8d 44 24 08          	lea    0x8(%esp),%eax
 8048c50:	50                   	push   %eax
 8048c51:	8d 44 24 10          	lea    0x10(%esp),%eax
 8048c55:	50                   	push   %eax
 8048c56:	68 4d a3 04 08       	push   $0x804a34d
 8048c5b:	ff 74 24 2c          	pushl  0x2c(%esp)
 8048c5f:	e8 9c fb ff ff       	call   8048800 <__isoc99_sscanf@plt>
 8048c64:	83 c4 10             	add    $0x10,%esp
 8048c67:	83 f8 02             	cmp    $0x2,%eax
 8048c6a:	75 07                	jne    8048c73 <phase_4+0x2a>
 8048c6c:	83 7c 24 0c 0e       	cmpl   $0xe,0xc(%esp)
 8048c71:	76 05                	jbe    8048c78 <phase_4+0x2f>
 8048c73:	e8 16 05 00 00       	call   804918e <explode_bomb>
 8048c78:	83 ec 04             	sub    $0x4,%esp
 8048c7b:	6a 0e                	push   $0xe
 8048c7d:	6a 00                	push   $0x0
 8048c7f:	ff 74 24 18          	pushl  0x18(%esp)
 8048c83:	e8 63 ff ff ff       	call   8048beb <func4>
 8048c88:	83 c4 10             	add    $0x10,%esp
 8048c8b:	83 f8 04             	cmp    $0x4,%eax
 8048c8e:	75 07                	jne    8048c97 <phase_4+0x4e>
 8048c90:	83 7c 24 08 04       	cmpl   $0x4,0x8(%esp)
 8048c95:	74 05                	je     8048c9c <phase_4+0x53>
 8048c97:	e8 f2 04 00 00       	call   804918e <explode_bomb>
 8048c9c:	83 c4 1c             	add    $0x1c,%esp
 8048c9f:	c3                   	ret    

08048ca0 <phase_5>:
 8048ca0:	53                   	push   %ebx
 8048ca1:	83 ec 24             	sub    $0x24,%esp
 8048ca4:	8b 5c 24 2c          	mov    0x2c(%esp),%ebx
 8048ca8:	53                   	push   %ebx
 8048ca9:	e8 53 02 00 00       	call   8048f01 <string_length>
 8048cae:	83 c4 10             	add    $0x10,%esp
 8048cb1:	83 f8 06             	cmp    $0x6,%eax
 8048cb4:	74 05                	je     8048cbb <phase_5+0x1b>
 8048cb6:	e8 d3 04 00 00       	call   804918e <explode_bomb>
 8048cbb:	b8 00 00 00 00       	mov    $0x0,%eax
 8048cc0:	0f b6 14 03          	movzbl (%ebx,%eax,1),%edx
 8048cc4:	83 e2 0f             	and    $0xf,%edx
 8048cc7:	0f b6 92 fc a0 04 08 	movzbl 0x804a0fc(%edx),%edx
 8048cce:	88 54 04 09          	mov    %dl,0x9(%esp,%eax,1)
 8048cd2:	83 c0 01             	add    $0x1,%eax
 8048cd5:	83 f8 06             	cmp    $0x6,%eax
 8048cd8:	75 e6                	jne    8048cc0 <phase_5+0x20>
 8048cda:	c6 44 24 0f 00       	movb   $0x0,0xf(%esp)
 8048cdf:	83 ec 08             	sub    $0x8,%esp
 8048ce2:	68 d2 a0 04 08       	push   $0x804a0d2
 8048ce7:	8d 44 24 15          	lea    0x15(%esp),%eax
 8048ceb:	50                   	push   %eax
 8048cec:	e8 2f 02 00 00       	call   8048f20 <strings_not_equal>
 8048cf1:	83 c4 10             	add    $0x10,%esp
 8048cf4:	85 c0                	test   %eax,%eax
 8048cf6:	74 05                	je     8048cfd <phase_5+0x5d>
 8048cf8:	e8 91 04 00 00       	call   804918e <explode_bomb>
 8048cfd:	83 c4 18             	add    $0x18,%esp
 8048d00:	5b                   	pop    %ebx
 8048d01:	c3                   	ret    

08048d02 <phase_6>:
 8048d02:	56                   	push   %esi
 8048d03:	53                   	push   %ebx
 8048d04:	83 ec 3c             	sub    $0x3c,%esp
 8048d07:	8d 44 24 20          	lea    0x20(%esp),%eax
 8048d0b:	50                   	push   %eax
 8048d0c:	ff 74 24 4c          	pushl  0x4c(%esp)
 8048d10:	e8 b6 04 00 00       	call   80491cb <read_six_numbers>
 8048d15:	83 c4 10             	add    $0x10,%esp
 8048d18:	be 00 00 00 00       	mov    $0x0,%esi
 8048d1d:	8b 44 b4 18          	mov    0x18(%esp,%esi,4),%eax
 8048d21:	83 e8 01             	sub    $0x1,%eax
 8048d24:	83 f8 05             	cmp    $0x5,%eax
 8048d27:	76 05                	jbe    8048d2e <phase_6+0x2c>
 8048d29:	e8 60 04 00 00       	call   804918e <explode_bomb>
 8048d2e:	83 c6 01             	add    $0x1,%esi
 8048d31:	83 fe 06             	cmp    $0x6,%esi
 8048d34:	74 1b                	je     8048d51 <phase_6+0x4f>
 8048d36:	89 f3                	mov    %esi,%ebx
 8048d38:	8b 44 9c 18          	mov    0x18(%esp,%ebx,4),%eax
 8048d3c:	39 44 b4 14          	cmp    %eax,0x14(%esp,%esi,4)
 8048d40:	75 05                	jne    8048d47 <phase_6+0x45>
 8048d42:	e8 47 04 00 00       	call   804918e <explode_bomb>
 8048d47:	83 c3 01             	add    $0x1,%ebx
 8048d4a:	83 fb 05             	cmp    $0x5,%ebx
 8048d4d:	7e e9                	jle    8048d38 <phase_6+0x36>
 8048d4f:	eb cc                	jmp    8048d1d <phase_6+0x1b>
 8048d51:	8d 44 24 18          	lea    0x18(%esp),%eax
 8048d55:	8d 5c 24 30          	lea    0x30(%esp),%ebx
 8048d59:	b9 07 00 00 00       	mov    $0x7,%ecx
 8048d5e:	89 ca                	mov    %ecx,%edx
 8048d60:	2b 10                	sub    (%eax),%edx
 8048d62:	89 10                	mov    %edx,(%eax)
 8048d64:	83 c0 04             	add    $0x4,%eax
 8048d67:	39 c3                	cmp    %eax,%ebx
 8048d69:	75 f3                	jne    8048d5e <phase_6+0x5c>
 8048d6b:	bb 00 00 00 00       	mov    $0x0,%ebx
 8048d70:	eb 15                	jmp    8048d87 <phase_6+0x85>
 8048d72:	8b 52 08             	mov    0x8(%edx),%edx
 8048d75:	83 c0 01             	add    $0x1,%eax
 8048d78:	39 c8                	cmp    %ecx,%eax
 8048d7a:	75 f6                	jne    8048d72 <phase_6+0x70>
 8048d7c:	89 14 b4             	mov    %edx,(%esp,%esi,4)
 8048d7f:	83 c3 01             	add    $0x1,%ebx
 8048d82:	83 fb 06             	cmp    $0x6,%ebx
 8048d85:	74 17                	je     8048d9e <phase_6+0x9c>
 8048d87:	89 de                	mov    %ebx,%esi
 8048d89:	8b 4c 9c 18          	mov    0x18(%esp,%ebx,4),%ecx
 8048d8d:	b8 01 00 00 00       	mov    $0x1,%eax
 8048d92:	ba 54 b2 04 08       	mov    $0x804b254,%edx
 8048d97:	83 f9 01             	cmp    $0x1,%ecx
 8048d9a:	7f d6                	jg     8048d72 <phase_6+0x70>
 8048d9c:	eb de                	jmp    8048d7c <phase_6+0x7a>
 8048d9e:	8b 1c 24             	mov    (%esp),%ebx
 8048da1:	89 e0                	mov    %esp,%eax
 8048da3:	8d 74 24 14          	lea    0x14(%esp),%esi
 8048da7:	89 d9                	mov    %ebx,%ecx
 8048da9:	8b 50 04             	mov    0x4(%eax),%edx
 8048dac:	89 51 08             	mov    %edx,0x8(%ecx)
 8048daf:	83 c0 04             	add    $0x4,%eax
 8048db2:	89 d1                	mov    %edx,%ecx
 8048db4:	39 c6                	cmp    %eax,%esi
 8048db6:	75 f1                	jne    8048da9 <phase_6+0xa7>
 8048db8:	c7 42 08 00 00 00 00 	movl   $0x0,0x8(%edx)
 8048dbf:	be 05 00 00 00       	mov    $0x5,%esi
 8048dc4:	8b 43 08             	mov    0x8(%ebx),%eax
 8048dc7:	8b 00                	mov    (%eax),%eax
 8048dc9:	39 03                	cmp    %eax,(%ebx)
 8048dcb:	7d 05                	jge    8048dd2 <phase_6+0xd0>
 8048dcd:	e8 bc 03 00 00       	call   804918e <explode_bomb>
 8048dd2:	8b 5b 08             	mov    0x8(%ebx),%ebx
 8048dd5:	83 ee 01             	sub    $0x1,%esi
 8048dd8:	75 ea                	jne    8048dc4 <phase_6+0xc2>
 8048dda:	83 c4 34             	add    $0x34,%esp
 8048ddd:	5b                   	pop    %ebx
 8048dde:	5e                   	pop    %esi
 8048ddf:	c3                   	ret    

08048de0 <fun7>:
 8048de0:	53                   	push   %ebx
 8048de1:	83 ec 08             	sub    $0x8,%esp
 8048de4:	8b 54 24 10          	mov    0x10(%esp),%edx
 8048de8:	8b 4c 24 14          	mov    0x14(%esp),%ecx
 8048dec:	85 d2                	test   %edx,%edx
 8048dee:	74 37                	je     8048e27 <fun7+0x47>
 8048df0:	8b 1a                	mov    (%edx),%ebx
 8048df2:	39 cb                	cmp    %ecx,%ebx
 8048df4:	7e 13                	jle    8048e09 <fun7+0x29>
 8048df6:	83 ec 08             	sub    $0x8,%esp
 8048df9:	51                   	push   %ecx
 8048dfa:	ff 72 04             	pushl  0x4(%edx)
 8048dfd:	e8 de ff ff ff       	call   8048de0 <fun7>
 8048e02:	83 c4 10             	add    $0x10,%esp
 8048e05:	01 c0                	add    %eax,%eax
 8048e07:	eb 23                	jmp    8048e2c <fun7+0x4c>
 8048e09:	b8 00 00 00 00       	mov    $0x0,%eax
 8048e0e:	39 cb                	cmp    %ecx,%ebx
 8048e10:	74 1a                	je     8048e2c <fun7+0x4c>
 8048e12:	83 ec 08             	sub    $0x8,%esp
 8048e15:	51                   	push   %ecx
 8048e16:	ff 72 08             	pushl  0x8(%edx)
 8048e19:	e8 c2 ff ff ff       	call   8048de0 <fun7>
 8048e1e:	83 c4 10             	add    $0x10,%esp
 8048e21:	8d 44 00 01          	lea    0x1(%eax,%eax,1),%eax
 8048e25:	eb 05                	jmp    8048e2c <fun7+0x4c>
 8048e27:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8048e2c:	83 c4 08             	add    $0x8,%esp
 8048e2f:	5b                   	pop    %ebx
 8048e30:	c3                   	ret    

08048e31 <secret_phase>:
 8048e31:	53                   	push   %ebx
 8048e32:	83 ec 08             	sub    $0x8,%esp
 8048e35:	e8 cc 03 00 00       	call   8049206 <read_line>
 8048e3a:	83 ec 04             	sub    $0x4,%esp
 8048e3d:	6a 0a                	push   $0xa
 8048e3f:	6a 00                	push   $0x0
 8048e41:	50                   	push   %eax
 8048e42:	e8 19 fa ff ff       	call   8048860 <strtol@plt>
 8048e47:	89 c3                	mov    %eax,%ebx
 8048e49:	8d 40 ff             	lea    -0x1(%eax),%eax
 8048e4c:	83 c4 10             	add    $0x10,%esp
 8048e4f:	3d e8 03 00 00       	cmp    $0x3e8,%eax
 8048e54:	76 05                	jbe    8048e5b <secret_phase+0x2a>
 8048e56:	e8 33 03 00 00       	call   804918e <explode_bomb>
 8048e5b:	83 ec 08             	sub    $0x8,%esp
 8048e5e:	53                   	push   %ebx
 8048e5f:	68 a0 b1 04 08       	push   $0x804b1a0
 8048e64:	e8 77 ff ff ff       	call   8048de0 <fun7>
 8048e69:	83 c4 10             	add    $0x10,%esp
 8048e6c:	83 f8 05             	cmp    $0x5,%eax
 8048e6f:	74 05                	je     8048e76 <secret_phase+0x45>
 8048e71:	e8 18 03 00 00       	call   804918e <explode_bomb>
 8048e76:	83 ec 0c             	sub    $0xc,%esp
 8048e79:	68 ac a0 04 08       	push   $0x804a0ac
 8048e7e:	e8 0d f9 ff ff       	call   8048790 <puts@plt>
 8048e83:	e8 77 04 00 00       	call   80492ff <phase_defused>
 8048e88:	83 c4 18             	add    $0x18,%esp
 8048e8b:	5b                   	pop    %ebx
 8048e8c:	c3                   	ret    

08048e8d <sig_handler>:
 8048e8d:	83 ec 18             	sub    $0x18,%esp
 8048e90:	68 0c a1 04 08       	push   $0x804a10c
 8048e95:	e8 f6 f8 ff ff       	call   8048790 <puts@plt>
 8048e9a:	c7 04 24 03 00 00 00 	movl   $0x3,(%esp)
 8048ea1:	e8 8a f8 ff ff       	call   8048730 <sleep@plt>
 8048ea6:	c7 04 24 c9 a2 04 08 	movl   $0x804a2c9,(%esp)
 8048ead:	e8 3e f8 ff ff       	call   80486f0 <printf@plt>
 8048eb2:	83 c4 04             	add    $0x4,%esp
 8048eb5:	ff 35 e4 b8 04 08    	pushl  0x804b8e4
 8048ebb:	e8 40 f8 ff ff       	call   8048700 <fflush@plt>
 8048ec0:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 8048ec7:	e8 64 f8 ff ff       	call   8048730 <sleep@plt>
 8048ecc:	c7 04 24 d1 a2 04 08 	movl   $0x804a2d1,(%esp)
 8048ed3:	e8 b8 f8 ff ff       	call   8048790 <puts@plt>
 8048ed8:	c7 04 24 10 00 00 00 	movl   $0x10,(%esp)
 8048edf:	e8 cc f8 ff ff       	call   80487b0 <exit@plt>

08048ee4 <invalid_phase>:
 8048ee4:	83 ec 14             	sub    $0x14,%esp
 8048ee7:	ff 74 24 18          	pushl  0x18(%esp)
 8048eeb:	68 d9 a2 04 08       	push   $0x804a2d9
 8048ef0:	e8 fb f7 ff ff       	call   80486f0 <printf@plt>
 8048ef5:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048efc:	e8 af f8 ff ff       	call   80487b0 <exit@plt>

08048f01 <string_length>:
 8048f01:	8b 54 24 04          	mov    0x4(%esp),%edx
 8048f05:	80 3a 00             	cmpb   $0x0,(%edx)
 8048f08:	74 10                	je     8048f1a <string_length+0x19>
 8048f0a:	b8 00 00 00 00       	mov    $0x0,%eax
 8048f0f:	83 c0 01             	add    $0x1,%eax
 8048f12:	80 3c 02 00          	cmpb   $0x0,(%edx,%eax,1)
 8048f16:	75 f7                	jne    8048f0f <string_length+0xe>
 8048f18:	f3 c3                	repz ret 
 8048f1a:	b8 00 00 00 00       	mov    $0x0,%eax
 8048f1f:	c3                   	ret    

08048f20 <strings_not_equal>:
 8048f20:	57                   	push   %edi
 8048f21:	56                   	push   %esi
 8048f22:	53                   	push   %ebx
 8048f23:	8b 5c 24 10          	mov    0x10(%esp),%ebx
 8048f27:	8b 74 24 14          	mov    0x14(%esp),%esi
 8048f2b:	53                   	push   %ebx
 8048f2c:	e8 d0 ff ff ff       	call   8048f01 <string_length>
 8048f31:	89 c7                	mov    %eax,%edi
 8048f33:	89 34 24             	mov    %esi,(%esp)
 8048f36:	e8 c6 ff ff ff       	call   8048f01 <string_length>
 8048f3b:	83 c4 04             	add    $0x4,%esp
 8048f3e:	ba 01 00 00 00       	mov    $0x1,%edx
 8048f43:	39 c7                	cmp    %eax,%edi
 8048f45:	75 38                	jne    8048f7f <strings_not_equal+0x5f>
 8048f47:	0f b6 03             	movzbl (%ebx),%eax
 8048f4a:	84 c0                	test   %al,%al
 8048f4c:	74 1e                	je     8048f6c <strings_not_equal+0x4c>
 8048f4e:	3a 06                	cmp    (%esi),%al
 8048f50:	74 06                	je     8048f58 <strings_not_equal+0x38>
 8048f52:	eb 1f                	jmp    8048f73 <strings_not_equal+0x53>
 8048f54:	3a 06                	cmp    (%esi),%al
 8048f56:	75 22                	jne    8048f7a <strings_not_equal+0x5a>
 8048f58:	83 c3 01             	add    $0x1,%ebx
 8048f5b:	83 c6 01             	add    $0x1,%esi
 8048f5e:	0f b6 03             	movzbl (%ebx),%eax
 8048f61:	84 c0                	test   %al,%al
 8048f63:	75 ef                	jne    8048f54 <strings_not_equal+0x34>
 8048f65:	ba 00 00 00 00       	mov    $0x0,%edx
 8048f6a:	eb 13                	jmp    8048f7f <strings_not_equal+0x5f>
 8048f6c:	ba 00 00 00 00       	mov    $0x0,%edx
 8048f71:	eb 0c                	jmp    8048f7f <strings_not_equal+0x5f>
 8048f73:	ba 01 00 00 00       	mov    $0x1,%edx
 8048f78:	eb 05                	jmp    8048f7f <strings_not_equal+0x5f>
 8048f7a:	ba 01 00 00 00       	mov    $0x1,%edx
 8048f7f:	89 d0                	mov    %edx,%eax
 8048f81:	5b                   	pop    %ebx
 8048f82:	5e                   	pop    %esi
 8048f83:	5f                   	pop    %edi
 8048f84:	c3                   	ret    

08048f85 <initialize_bomb>:
 8048f85:	56                   	push   %esi
 8048f86:	53                   	push   %ebx
 8048f87:	81 ec 4c 20 00 00    	sub    $0x204c,%esp
 8048f8d:	68 8d 8e 04 08       	push   $0x8048e8d
 8048f92:	6a 02                	push   $0x2
 8048f94:	e8 87 f7 ff ff       	call   8048720 <signal@plt>
 8048f99:	83 c4 08             	add    $0x8,%esp
 8048f9c:	6a 40                	push   $0x40
 8048f9e:	8d 84 24 0c 20 00 00 	lea    0x200c(%esp),%eax
 8048fa5:	50                   	push   %eax
 8048fa6:	e8 c5 f7 ff ff       	call   8048770 <gethostname@plt>
 8048fab:	83 c4 10             	add    $0x10,%esp
 8048fae:	85 c0                	test   %eax,%eax
 8048fb0:	75 17                	jne    8048fc9 <initialize_bomb+0x44>
 8048fb2:	a1 c0 b6 04 08       	mov    0x804b6c0,%eax
 8048fb7:	bb c4 b6 04 08       	mov    $0x804b6c4,%ebx
 8048fbc:	8d b4 24 00 20 00 00 	lea    0x2000(%esp),%esi
 8048fc3:	85 c0                	test   %eax,%eax
 8048fc5:	75 1b                	jne    8048fe2 <initialize_bomb+0x5d>
 8048fc7:	eb 54                	jmp    804901d <initialize_bomb+0x98>
 8048fc9:	83 ec 0c             	sub    $0xc,%esp
 8048fcc:	68 44 a1 04 08       	push   $0x804a144
 8048fd1:	e8 ba f7 ff ff       	call   8048790 <puts@plt>
 8048fd6:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8048fdd:	e8 ce f7 ff ff       	call   80487b0 <exit@plt>
 8048fe2:	83 ec 08             	sub    $0x8,%esp
 8048fe5:	56                   	push   %esi
 8048fe6:	50                   	push   %eax
 8048fe7:	e8 04 f8 ff ff       	call   80487f0 <strcasecmp@plt>
 8048fec:	83 c4 10             	add    $0x10,%esp
 8048fef:	85 c0                	test   %eax,%eax
 8048ff1:	74 43                	je     8049036 <initialize_bomb+0xb1>
 8048ff3:	83 c3 04             	add    $0x4,%ebx
 8048ff6:	8b 43 fc             	mov    -0x4(%ebx),%eax
 8048ff9:	85 c0                	test   %eax,%eax
 8048ffb:	75 e5                	jne    8048fe2 <initialize_bomb+0x5d>
 8048ffd:	eb 1e                	jmp    804901d <initialize_bomb+0x98>
 8048fff:	83 ec 08             	sub    $0x8,%esp
 8049002:	8d 44 24 08          	lea    0x8(%esp),%eax
 8049006:	50                   	push   %eax
 8049007:	68 ea a2 04 08       	push   $0x804a2ea
 804900c:	e8 df f6 ff ff       	call   80486f0 <printf@plt>
 8049011:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049018:	e8 93 f7 ff ff       	call   80487b0 <exit@plt>
 804901d:	83 ec 0c             	sub    $0xc,%esp
 8049020:	68 7c a1 04 08       	push   $0x804a17c
 8049025:	e8 66 f7 ff ff       	call   8048790 <puts@plt>
 804902a:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049031:	e8 7a f7 ff ff       	call   80487b0 <exit@plt>
 8049036:	83 ec 0c             	sub    $0xc,%esp
 8049039:	8d 44 24 0c          	lea    0xc(%esp),%eax
 804903d:	50                   	push   %eax
 804903e:	e8 4b 0c 00 00       	call   8049c8e <init_driver>
 8049043:	83 c4 10             	add    $0x10,%esp
 8049046:	85 c0                	test   %eax,%eax
 8049048:	78 b5                	js     8048fff <initialize_bomb+0x7a>
 804904a:	81 c4 44 20 00 00    	add    $0x2044,%esp
 8049050:	5b                   	pop    %ebx
 8049051:	5e                   	pop    %esi
 8049052:	c3                   	ret    

08049053 <initialize_bomb_solve>:
 8049053:	f3 c3                	repz ret 

08049055 <blank_line>:
 8049055:	56                   	push   %esi
 8049056:	53                   	push   %ebx
 8049057:	83 ec 04             	sub    $0x4,%esp
 804905a:	8b 74 24 10          	mov    0x10(%esp),%esi
 804905e:	eb 14                	jmp    8049074 <blank_line+0x1f>
 8049060:	e8 2b f8 ff ff       	call   8048890 <__ctype_b_loc@plt>
 8049065:	83 c6 01             	add    $0x1,%esi
 8049068:	0f be db             	movsbl %bl,%ebx
 804906b:	8b 00                	mov    (%eax),%eax
 804906d:	f6 44 58 01 20       	testb  $0x20,0x1(%eax,%ebx,2)
 8049072:	74 0e                	je     8049082 <blank_line+0x2d>
 8049074:	0f b6 1e             	movzbl (%esi),%ebx
 8049077:	84 db                	test   %bl,%bl
 8049079:	75 e5                	jne    8049060 <blank_line+0xb>
 804907b:	b8 01 00 00 00       	mov    $0x1,%eax
 8049080:	eb 05                	jmp    8049087 <blank_line+0x32>
 8049082:	b8 00 00 00 00       	mov    $0x0,%eax
 8049087:	83 c4 04             	add    $0x4,%esp
 804908a:	5b                   	pop    %ebx
 804908b:	5e                   	pop    %esi
 804908c:	c3                   	ret    

0804908d <skip>:
 804908d:	53                   	push   %ebx
 804908e:	83 ec 08             	sub    $0x8,%esp
 8049091:	83 ec 04             	sub    $0x4,%esp
 8049094:	ff 35 f0 b8 04 08    	pushl  0x804b8f0
 804909a:	6a 50                	push   $0x50
 804909c:	a1 ec b8 04 08       	mov    0x804b8ec,%eax
 80490a1:	8d 04 80             	lea    (%eax,%eax,4),%eax
 80490a4:	c1 e0 04             	shl    $0x4,%eax
 80490a7:	05 00 b9 04 08       	add    $0x804b900,%eax
 80490ac:	50                   	push   %eax
 80490ad:	e8 5e f6 ff ff       	call   8048710 <fgets@plt>
 80490b2:	89 c3                	mov    %eax,%ebx
 80490b4:	83 c4 10             	add    $0x10,%esp
 80490b7:	85 c0                	test   %eax,%eax
 80490b9:	74 10                	je     80490cb <skip+0x3e>
 80490bb:	83 ec 0c             	sub    $0xc,%esp
 80490be:	50                   	push   %eax
 80490bf:	e8 91 ff ff ff       	call   8049055 <blank_line>
 80490c4:	83 c4 10             	add    $0x10,%esp
 80490c7:	85 c0                	test   %eax,%eax
 80490c9:	75 c6                	jne    8049091 <skip+0x4>
 80490cb:	89 d8                	mov    %ebx,%eax
 80490cd:	83 c4 08             	add    $0x8,%esp
 80490d0:	5b                   	pop    %ebx
 80490d1:	c3                   	ret    

080490d2 <send_msg>:
 80490d2:	57                   	push   %edi
 80490d3:	53                   	push   %ebx
 80490d4:	81 ec 04 40 00 00    	sub    $0x4004,%esp
 80490da:	8b 1d ec b8 04 08    	mov    0x804b8ec,%ebx
 80490e0:	8d 54 9b fb          	lea    -0x5(%ebx,%ebx,4),%edx
 80490e4:	c1 e2 04             	shl    $0x4,%edx
 80490e7:	81 c2 00 b9 04 08    	add    $0x804b900,%edx
 80490ed:	b8 00 00 00 00       	mov    $0x0,%eax
 80490f2:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 80490f7:	89 d7                	mov    %edx,%edi
 80490f9:	f2 ae                	repnz scas %es:(%edi),%al
 80490fb:	f7 d1                	not    %ecx
 80490fd:	83 c1 63             	add    $0x63,%ecx
 8049100:	81 f9 00 20 00 00    	cmp    $0x2000,%ecx
 8049106:	76 19                	jbe    8049121 <send_msg+0x4f>
 8049108:	83 ec 0c             	sub    $0xc,%esp
 804910b:	68 b4 a1 04 08       	push   $0x804a1b4
 8049110:	e8 db f5 ff ff       	call   80486f0 <printf@plt>
 8049115:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 804911c:	e8 8f f6 ff ff       	call   80487b0 <exit@plt>
 8049121:	83 bc 24 10 40 00 00 	cmpl   $0x0,0x4010(%esp)
 8049128:	00 
 8049129:	b9 0c a3 04 08       	mov    $0x804a30c,%ecx
 804912e:	b8 04 a3 04 08       	mov    $0x804a304,%eax
 8049133:	0f 44 c1             	cmove  %ecx,%eax
 8049136:	83 ec 08             	sub    $0x8,%esp
 8049139:	52                   	push   %edx
 804913a:	53                   	push   %ebx
 804913b:	50                   	push   %eax
 804913c:	ff 35 a0 b6 04 08    	pushl  0x804b6a0
 8049142:	68 15 a3 04 08       	push   $0x804a315
 8049147:	8d 9c 24 1c 20 00 00 	lea    0x201c(%esp),%ebx
 804914e:	53                   	push   %ebx
 804914f:	e8 dc f6 ff ff       	call   8048830 <sprintf@plt>
 8049154:	83 c4 20             	add    $0x20,%esp
 8049157:	54                   	push   %esp
 8049158:	6a 00                	push   $0x0
 804915a:	53                   	push   %ebx
 804915b:	68 a0 b2 04 08       	push   $0x804b2a0
 8049160:	e8 d5 0c 00 00       	call   8049e3a <driver_post>
 8049165:	83 c4 10             	add    $0x10,%esp
 8049168:	85 c0                	test   %eax,%eax
 804916a:	79 19                	jns    8049185 <send_msg+0xb3>
 804916c:	83 ec 0c             	sub    $0xc,%esp
 804916f:	8d 44 24 0c          	lea    0xc(%esp),%eax
 8049173:	50                   	push   %eax
 8049174:	e8 17 f6 ff ff       	call   8048790 <puts@plt>
 8049179:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8049180:	e8 2b f6 ff ff       	call   80487b0 <exit@plt>
 8049185:	81 c4 04 40 00 00    	add    $0x4004,%esp
 804918b:	5b                   	pop    %ebx
 804918c:	5f                   	pop    %edi
 804918d:	c3                   	ret    

0804918e <explode_bomb>:
 804918e:	83 ec 18             	sub    $0x18,%esp
 8049191:	68 21 a3 04 08       	push   $0x804a321
 8049196:	e8 f5 f5 ff ff       	call   8048790 <puts@plt>
 804919b:	c7 04 24 2a a3 04 08 	movl   $0x804a32a,(%esp)
 80491a2:	e8 e9 f5 ff ff       	call   8048790 <puts@plt>
 80491a7:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 80491ae:	e8 1f ff ff ff       	call   80490d2 <send_msg>
 80491b3:	c7 04 24 d8 a1 04 08 	movl   $0x804a1d8,(%esp)
 80491ba:	e8 d1 f5 ff ff       	call   8048790 <puts@plt>
 80491bf:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 80491c6:	e8 e5 f5 ff ff       	call   80487b0 <exit@plt>

080491cb <read_six_numbers>:
 80491cb:	83 ec 0c             	sub    $0xc,%esp
 80491ce:	8b 44 24 14          	mov    0x14(%esp),%eax
 80491d2:	8d 50 14             	lea    0x14(%eax),%edx
 80491d5:	52                   	push   %edx
 80491d6:	8d 50 10             	lea    0x10(%eax),%edx
 80491d9:	52                   	push   %edx
 80491da:	8d 50 0c             	lea    0xc(%eax),%edx
 80491dd:	52                   	push   %edx
 80491de:	8d 50 08             	lea    0x8(%eax),%edx
 80491e1:	52                   	push   %edx
 80491e2:	8d 50 04             	lea    0x4(%eax),%edx
 80491e5:	52                   	push   %edx
 80491e6:	50                   	push   %eax
 80491e7:	68 41 a3 04 08       	push   $0x804a341
 80491ec:	ff 74 24 2c          	pushl  0x2c(%esp)
 80491f0:	e8 0b f6 ff ff       	call   8048800 <__isoc99_sscanf@plt>
 80491f5:	83 c4 20             	add    $0x20,%esp
 80491f8:	83 f8 05             	cmp    $0x5,%eax
 80491fb:	7f 05                	jg     8049202 <read_six_numbers+0x37>
 80491fd:	e8 8c ff ff ff       	call   804918e <explode_bomb>
 8049202:	83 c4 0c             	add    $0xc,%esp
 8049205:	c3                   	ret    

08049206 <read_line>:
 8049206:	57                   	push   %edi
 8049207:	56                   	push   %esi
 8049208:	53                   	push   %ebx
 8049209:	e8 7f fe ff ff       	call   804908d <skip>
 804920e:	85 c0                	test   %eax,%eax
 8049210:	75 70                	jne    8049282 <read_line+0x7c>
 8049212:	a1 e0 b8 04 08       	mov    0x804b8e0,%eax
 8049217:	39 05 f0 b8 04 08    	cmp    %eax,0x804b8f0
 804921d:	75 19                	jne    8049238 <read_line+0x32>
 804921f:	83 ec 0c             	sub    $0xc,%esp
 8049222:	68 53 a3 04 08       	push   $0x804a353
 8049227:	e8 64 f5 ff ff       	call   8048790 <puts@plt>
 804922c:	c7 04 24 08 00 00 00 	movl   $0x8,(%esp)
 8049233:	e8 78 f5 ff ff       	call   80487b0 <exit@plt>
 8049238:	83 ec 0c             	sub    $0xc,%esp
 804923b:	68 71 a3 04 08       	push   $0x804a371
 8049240:	e8 3b f5 ff ff       	call   8048780 <getenv@plt>
 8049245:	83 c4 10             	add    $0x10,%esp
 8049248:	85 c0                	test   %eax,%eax
 804924a:	74 0a                	je     8049256 <read_line+0x50>
 804924c:	83 ec 0c             	sub    $0xc,%esp
 804924f:	6a 00                	push   $0x0
 8049251:	e8 5a f5 ff ff       	call   80487b0 <exit@plt>
 8049256:	a1 e0 b8 04 08       	mov    0x804b8e0,%eax
 804925b:	a3 f0 b8 04 08       	mov    %eax,0x804b8f0
 8049260:	e8 28 fe ff ff       	call   804908d <skip>
 8049265:	85 c0                	test   %eax,%eax
 8049267:	75 19                	jne    8049282 <read_line+0x7c>
 8049269:	83 ec 0c             	sub    $0xc,%esp
 804926c:	68 53 a3 04 08       	push   $0x804a353
 8049271:	e8 1a f5 ff ff       	call   8048790 <puts@plt>
 8049276:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 804927d:	e8 2e f5 ff ff       	call   80487b0 <exit@plt>
 8049282:	8b 15 ec b8 04 08    	mov    0x804b8ec,%edx
 8049288:	8d 1c 92             	lea    (%edx,%edx,4),%ebx
 804928b:	c1 e3 04             	shl    $0x4,%ebx
 804928e:	81 c3 00 b9 04 08    	add    $0x804b900,%ebx
 8049294:	b8 00 00 00 00       	mov    $0x0,%eax
 8049299:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 804929e:	89 df                	mov    %ebx,%edi
 80492a0:	f2 ae                	repnz scas %es:(%edi),%al
 80492a2:	f7 d1                	not    %ecx
 80492a4:	83 e9 01             	sub    $0x1,%ecx
 80492a7:	83 f9 4e             	cmp    $0x4e,%ecx
 80492aa:	7e 36                	jle    80492e2 <read_line+0xdc>
 80492ac:	83 ec 0c             	sub    $0xc,%esp
 80492af:	68 7c a3 04 08       	push   $0x804a37c
 80492b4:	e8 d7 f4 ff ff       	call   8048790 <puts@plt>
 80492b9:	a1 ec b8 04 08       	mov    0x804b8ec,%eax
 80492be:	8d 50 01             	lea    0x1(%eax),%edx
 80492c1:	89 15 ec b8 04 08    	mov    %edx,0x804b8ec
 80492c7:	6b c0 50             	imul   $0x50,%eax,%eax
 80492ca:	05 00 b9 04 08       	add    $0x804b900,%eax
 80492cf:	be 97 a3 04 08       	mov    $0x804a397,%esi
 80492d4:	b9 04 00 00 00       	mov    $0x4,%ecx
 80492d9:	89 c7                	mov    %eax,%edi
 80492db:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 80492dd:	e8 ac fe ff ff       	call   804918e <explode_bomb>
 80492e2:	8d 04 92             	lea    (%edx,%edx,4),%eax
 80492e5:	c1 e0 04             	shl    $0x4,%eax
 80492e8:	c6 84 01 ff b8 04 08 	movb   $0x0,0x804b8ff(%ecx,%eax,1)
 80492ef:	00 
 80492f0:	83 c2 01             	add    $0x1,%edx
 80492f3:	89 15 ec b8 04 08    	mov    %edx,0x804b8ec
 80492f9:	89 d8                	mov    %ebx,%eax
 80492fb:	5b                   	pop    %ebx
 80492fc:	5e                   	pop    %esi
 80492fd:	5f                   	pop    %edi
 80492fe:	c3                   	ret    

080492ff <phase_defused>:
 80492ff:	83 ec 78             	sub    $0x78,%esp
 8049302:	6a 01                	push   $0x1
 8049304:	e8 c9 fd ff ff       	call   80490d2 <send_msg>
 8049309:	83 c4 10             	add    $0x10,%esp
 804930c:	83 3d ec b8 04 08 06 	cmpl   $0x6,0x804b8ec
 8049313:	75 7f                	jne    8049394 <phase_defused+0x95>
 8049315:	83 ec 0c             	sub    $0xc,%esp
 8049318:	8d 44 24 1c          	lea    0x1c(%esp),%eax
 804931c:	50                   	push   %eax
 804931d:	8d 44 24 18          	lea    0x18(%esp),%eax
 8049321:	50                   	push   %eax
 8049322:	8d 44 24 20          	lea    0x20(%esp),%eax
 8049326:	50                   	push   %eax
 8049327:	68 a7 a3 04 08       	push   $0x804a3a7
 804932c:	68 f0 b9 04 08       	push   $0x804b9f0
 8049331:	e8 ca f4 ff ff       	call   8048800 <__isoc99_sscanf@plt>
 8049336:	83 c4 20             	add    $0x20,%esp
 8049339:	83 f8 03             	cmp    $0x3,%eax
 804933c:	75 3a                	jne    8049378 <phase_defused+0x79>
 804933e:	83 ec 08             	sub    $0x8,%esp
 8049341:	68 b0 a3 04 08       	push   $0x804a3b0
 8049346:	8d 44 24 1c          	lea    0x1c(%esp),%eax
 804934a:	50                   	push   %eax
 804934b:	e8 d0 fb ff ff       	call   8048f20 <strings_not_equal>
 8049350:	83 c4 10             	add    $0x10,%esp
 8049353:	85 c0                	test   %eax,%eax
 8049355:	75 21                	jne    8049378 <phase_defused+0x79>
 8049357:	83 ec 0c             	sub    $0xc,%esp
 804935a:	68 fc a1 04 08       	push   $0x804a1fc
 804935f:	e8 2c f4 ff ff       	call   8048790 <puts@plt>
 8049364:	c7 04 24 24 a2 04 08 	movl   $0x804a224,(%esp)
 804936b:	e8 20 f4 ff ff       	call   8048790 <puts@plt>
 8049370:	e8 bc fa ff ff       	call   8048e31 <secret_phase>
 8049375:	83 c4 10             	add    $0x10,%esp
 8049378:	83 ec 0c             	sub    $0xc,%esp
 804937b:	68 5c a2 04 08       	push   $0x804a25c
 8049380:	e8 0b f4 ff ff       	call   8048790 <puts@plt>
 8049385:	c7 04 24 88 a2 04 08 	movl   $0x804a288,(%esp)
 804938c:	e8 ff f3 ff ff       	call   8048790 <puts@plt>
 8049391:	83 c4 10             	add    $0x10,%esp
 8049394:	83 c4 6c             	add    $0x6c,%esp
 8049397:	c3                   	ret    

08049398 <sigalrm_handler>:
 8049398:	83 ec 10             	sub    $0x10,%esp
 804939b:	6a 00                	push   $0x0
 804939d:	68 78 a4 04 08       	push   $0x804a478
 80493a2:	ff 35 c0 b8 04 08    	pushl  0x804b8c0
 80493a8:	e8 23 f4 ff ff       	call   80487d0 <fprintf@plt>
 80493ad:	c7 04 24 01 00 00 00 	movl   $0x1,(%esp)
 80493b4:	e8 f7 f3 ff ff       	call   80487b0 <exit@plt>

080493b9 <rio_readlineb>:
 80493b9:	55                   	push   %ebp
 80493ba:	57                   	push   %edi
 80493bb:	56                   	push   %esi
 80493bc:	53                   	push   %ebx
 80493bd:	83 ec 2c             	sub    $0x2c,%esp
 80493c0:	89 d7                	mov    %edx,%edi
 80493c2:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
 80493c6:	83 f9 01             	cmp    $0x1,%ecx
 80493c9:	76 79                	jbe    8049444 <rio_readlineb+0x8b>
 80493cb:	89 c3                	mov    %eax,%ebx
 80493cd:	89 4c 24 08          	mov    %ecx,0x8(%esp)
 80493d1:	bd 01 00 00 00       	mov    $0x1,%ebp
 80493d6:	8d 73 0c             	lea    0xc(%ebx),%esi
 80493d9:	eb 2d                	jmp    8049408 <rio_readlineb+0x4f>
 80493db:	83 ec 04             	sub    $0x4,%esp
 80493de:	68 00 20 00 00       	push   $0x2000
 80493e3:	56                   	push   %esi
 80493e4:	ff 33                	pushl  (%ebx)
 80493e6:	e8 f5 f2 ff ff       	call   80486e0 <read@plt>
 80493eb:	89 43 04             	mov    %eax,0x4(%ebx)
 80493ee:	83 c4 10             	add    $0x10,%esp
 80493f1:	85 c0                	test   %eax,%eax
 80493f3:	79 0c                	jns    8049401 <rio_readlineb+0x48>
 80493f5:	e8 26 f4 ff ff       	call   8048820 <__errno_location@plt>
 80493fa:	83 38 04             	cmpl   $0x4,(%eax)
 80493fd:	74 09                	je     8049408 <rio_readlineb+0x4f>
 80493ff:	eb 55                	jmp    8049456 <rio_readlineb+0x9d>
 8049401:	85 c0                	test   %eax,%eax
 8049403:	74 56                	je     804945b <rio_readlineb+0xa2>
 8049405:	89 73 08             	mov    %esi,0x8(%ebx)
 8049408:	8b 43 04             	mov    0x4(%ebx),%eax
 804940b:	85 c0                	test   %eax,%eax
 804940d:	7e cc                	jle    80493db <rio_readlineb+0x22>
 804940f:	8b 4b 08             	mov    0x8(%ebx),%ecx
 8049412:	0f b6 11             	movzbl (%ecx),%edx
 8049415:	88 54 24 1f          	mov    %dl,0x1f(%esp)
 8049419:	83 c1 01             	add    $0x1,%ecx
 804941c:	89 4b 08             	mov    %ecx,0x8(%ebx)
 804941f:	83 e8 01             	sub    $0x1,%eax
 8049422:	89 43 04             	mov    %eax,0x4(%ebx)
 8049425:	83 c7 01             	add    $0x1,%edi
 8049428:	88 57 ff             	mov    %dl,-0x1(%edi)
 804942b:	80 fa 0a             	cmp    $0xa,%dl
 804942e:	75 09                	jne    8049439 <rio_readlineb+0x80>
 8049430:	eb 1d                	jmp    804944f <rio_readlineb+0x96>
 8049432:	83 fd 01             	cmp    $0x1,%ebp
 8049435:	75 18                	jne    804944f <rio_readlineb+0x96>
 8049437:	eb 2b                	jmp    8049464 <rio_readlineb+0xab>
 8049439:	83 c5 01             	add    $0x1,%ebp
 804943c:	3b 6c 24 08          	cmp    0x8(%esp),%ebp
 8049440:	74 09                	je     804944b <rio_readlineb+0x92>
 8049442:	eb c4                	jmp    8049408 <rio_readlineb+0x4f>
 8049444:	bd 01 00 00 00       	mov    $0x1,%ebp
 8049449:	eb 04                	jmp    804944f <rio_readlineb+0x96>
 804944b:	8b 6c 24 0c          	mov    0xc(%esp),%ebp
 804944f:	c6 07 00             	movb   $0x0,(%edi)
 8049452:	89 e8                	mov    %ebp,%eax
 8049454:	eb 0e                	jmp    8049464 <rio_readlineb+0xab>
 8049456:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804945b:	85 c0                	test   %eax,%eax
 804945d:	74 d3                	je     8049432 <rio_readlineb+0x79>
 804945f:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049464:	83 c4 2c             	add    $0x2c,%esp
 8049467:	5b                   	pop    %ebx
 8049468:	5e                   	pop    %esi
 8049469:	5f                   	pop    %edi
 804946a:	5d                   	pop    %ebp
 804946b:	c3                   	ret    

0804946c <submitr>:
 804946c:	55                   	push   %ebp
 804946d:	57                   	push   %edi
 804946e:	56                   	push   %esi
 804946f:	53                   	push   %ebx
 8049470:	81 ec 50 a0 00 00    	sub    $0xa050,%esp
 8049476:	8b 9c 24 78 a0 00 00 	mov    0xa078(%esp),%ebx
 804947d:	c7 84 24 24 20 00 00 	movl   $0x0,0x2024(%esp)
 8049484:	00 00 00 00 
 8049488:	6a 00                	push   $0x0
 804948a:	6a 01                	push   $0x1
 804948c:	6a 02                	push   $0x2
 804948e:	e8 ad f3 ff ff       	call   8048840 <socket@plt>
 8049493:	89 44 24 18          	mov    %eax,0x18(%esp)
 8049497:	83 c4 10             	add    $0x10,%esp
 804949a:	85 c0                	test   %eax,%eax
 804949c:	79 55                	jns    80494f3 <submitr+0x87>
 804949e:	8b 84 24 78 a0 00 00 	mov    0xa078(%esp),%eax
 80494a5:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80494ab:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 80494b2:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 80494b9:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 80494c0:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 80494c7:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 80494ce:	c7 40 18 63 72 65 61 	movl   $0x61657263,0x18(%eax)
 80494d5:	c7 40 1c 74 65 20 73 	movl   $0x73206574,0x1c(%eax)
 80494dc:	c7 40 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%eax)
 80494e3:	66 c7 40 24 74 00    	movw   $0x74,0x24(%eax)
 80494e9:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80494ee:	e9 5b 07 00 00       	jmp    8049c4e <submitr+0x7e2>
 80494f3:	83 ec 0c             	sub    $0xc,%esp
 80494f6:	ff b4 24 6c a0 00 00 	pushl  0xa06c(%esp)
 80494fd:	e8 4e f3 ff ff       	call   8048850 <gethostbyname@plt>
 8049502:	83 c4 10             	add    $0x10,%esp
 8049505:	85 c0                	test   %eax,%eax
 8049507:	75 76                	jne    804957f <submitr+0x113>
 8049509:	8b 84 24 78 a0 00 00 	mov    0xa078(%esp),%eax
 8049510:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049516:	c7 40 04 72 3a 20 44 	movl   $0x44203a72,0x4(%eax)
 804951d:	c7 40 08 4e 53 20 69 	movl   $0x6920534e,0x8(%eax)
 8049524:	c7 40 0c 73 20 75 6e 	movl   $0x6e752073,0xc(%eax)
 804952b:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049532:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049539:	c7 40 18 72 65 73 6f 	movl   $0x6f736572,0x18(%eax)
 8049540:	c7 40 1c 6c 76 65 20 	movl   $0x2065766c,0x1c(%eax)
 8049547:	c7 40 20 73 65 72 76 	movl   $0x76726573,0x20(%eax)
 804954e:	c7 40 24 65 72 20 61 	movl   $0x61207265,0x24(%eax)
 8049555:	c7 40 28 64 64 72 65 	movl   $0x65726464,0x28(%eax)
 804955c:	66 c7 40 2c 73 73    	movw   $0x7373,0x2c(%eax)
 8049562:	c6 40 2e 00          	movb   $0x0,0x2e(%eax)
 8049566:	83 ec 0c             	sub    $0xc,%esp
 8049569:	ff 74 24 14          	pushl  0x14(%esp)
 804956d:	e8 0e f3 ff ff       	call   8048880 <close@plt>
 8049572:	83 c4 10             	add    $0x10,%esp
 8049575:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804957a:	e9 cf 06 00 00       	jmp    8049c4e <submitr+0x7e2>
 804957f:	8d b4 24 30 a0 00 00 	lea    0xa030(%esp),%esi
 8049586:	c7 84 24 30 a0 00 00 	movl   $0x0,0xa030(%esp)
 804958d:	00 00 00 00 
 8049591:	c7 84 24 34 a0 00 00 	movl   $0x0,0xa034(%esp)
 8049598:	00 00 00 00 
 804959c:	c7 84 24 38 a0 00 00 	movl   $0x0,0xa038(%esp)
 80495a3:	00 00 00 00 
 80495a7:	c7 84 24 3c a0 00 00 	movl   $0x0,0xa03c(%esp)
 80495ae:	00 00 00 00 
 80495b2:	66 c7 84 24 30 a0 00 	movw   $0x2,0xa030(%esp)
 80495b9:	00 02 00 
 80495bc:	83 ec 04             	sub    $0x4,%esp
 80495bf:	ff 70 0c             	pushl  0xc(%eax)
 80495c2:	8d 94 24 3c a0 00 00 	lea    0xa03c(%esp),%edx
 80495c9:	52                   	push   %edx
 80495ca:	8b 40 10             	mov    0x10(%eax),%eax
 80495cd:	ff 30                	pushl  (%eax)
 80495cf:	e8 7c f1 ff ff       	call   8048750 <bcopy@plt>
 80495d4:	0f b7 84 24 74 a0 00 	movzwl 0xa074(%esp),%eax
 80495db:	00 
 80495dc:	66 c1 c8 08          	ror    $0x8,%ax
 80495e0:	66 89 84 24 42 a0 00 	mov    %ax,0xa042(%esp)
 80495e7:	00 
 80495e8:	83 c4 0c             	add    $0xc,%esp
 80495eb:	6a 10                	push   $0x10
 80495ed:	56                   	push   %esi
 80495ee:	ff 74 24 14          	pushl  0x14(%esp)
 80495f2:	e8 79 f2 ff ff       	call   8048870 <connect@plt>
 80495f7:	83 c4 10             	add    $0x10,%esp
 80495fa:	85 c0                	test   %eax,%eax
 80495fc:	79 68                	jns    8049666 <submitr+0x1fa>
 80495fe:	8b 84 24 78 a0 00 00 	mov    0xa078(%esp),%eax
 8049605:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 804960b:	c7 40 04 72 3a 20 55 	movl   $0x55203a72,0x4(%eax)
 8049612:	c7 40 08 6e 61 62 6c 	movl   $0x6c62616e,0x8(%eax)
 8049619:	c7 40 0c 65 20 74 6f 	movl   $0x6f742065,0xc(%eax)
 8049620:	c7 40 10 20 63 6f 6e 	movl   $0x6e6f6320,0x10(%eax)
 8049627:	c7 40 14 6e 65 63 74 	movl   $0x7463656e,0x14(%eax)
 804962e:	c7 40 18 20 74 6f 20 	movl   $0x206f7420,0x18(%eax)
 8049635:	c7 40 1c 74 68 65 20 	movl   $0x20656874,0x1c(%eax)
 804963c:	c7 40 20 73 65 72 76 	movl   $0x76726573,0x20(%eax)
 8049643:	66 c7 40 24 65 72    	movw   $0x7265,0x24(%eax)
 8049649:	c6 40 26 00          	movb   $0x0,0x26(%eax)
 804964d:	83 ec 0c             	sub    $0xc,%esp
 8049650:	ff 74 24 14          	pushl  0x14(%esp)
 8049654:	e8 27 f2 ff ff       	call   8048880 <close@plt>
 8049659:	83 c4 10             	add    $0x10,%esp
 804965c:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049661:	e9 e8 05 00 00       	jmp    8049c4e <submitr+0x7e2>
 8049666:	be ff ff ff ff       	mov    $0xffffffff,%esi
 804966b:	b8 00 00 00 00       	mov    $0x0,%eax
 8049670:	89 f1                	mov    %esi,%ecx
 8049672:	89 df                	mov    %ebx,%edi
 8049674:	f2 ae                	repnz scas %es:(%edi),%al
 8049676:	f7 d1                	not    %ecx
 8049678:	89 cd                	mov    %ecx,%ebp
 804967a:	89 f1                	mov    %esi,%ecx
 804967c:	8b bc 24 68 a0 00 00 	mov    0xa068(%esp),%edi
 8049683:	f2 ae                	repnz scas %es:(%edi),%al
 8049685:	89 4c 24 0c          	mov    %ecx,0xc(%esp)
 8049689:	89 f1                	mov    %esi,%ecx
 804968b:	8b bc 24 6c a0 00 00 	mov    0xa06c(%esp),%edi
 8049692:	f2 ae                	repnz scas %es:(%edi),%al
 8049694:	89 ca                	mov    %ecx,%edx
 8049696:	f7 d2                	not    %edx
 8049698:	89 f1                	mov    %esi,%ecx
 804969a:	8b bc 24 70 a0 00 00 	mov    0xa070(%esp),%edi
 80496a1:	f2 ae                	repnz scas %es:(%edi),%al
 80496a3:	2b 54 24 0c          	sub    0xc(%esp),%edx
 80496a7:	29 ca                	sub    %ecx,%edx
 80496a9:	8d 44 6d fd          	lea    -0x3(%ebp,%ebp,2),%eax
 80496ad:	8d 44 02 7b          	lea    0x7b(%edx,%eax,1),%eax
 80496b1:	3d 00 20 00 00       	cmp    $0x2000,%eax
 80496b6:	0f 86 81 00 00 00    	jbe    804973d <submitr+0x2d1>
 80496bc:	8b 84 24 78 a0 00 00 	mov    0xa078(%esp),%eax
 80496c3:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80496c9:	c7 40 04 72 3a 20 52 	movl   $0x52203a72,0x4(%eax)
 80496d0:	c7 40 08 65 73 75 6c 	movl   $0x6c757365,0x8(%eax)
 80496d7:	c7 40 0c 74 20 73 74 	movl   $0x74732074,0xc(%eax)
 80496de:	c7 40 10 72 69 6e 67 	movl   $0x676e6972,0x10(%eax)
 80496e5:	c7 40 14 20 74 6f 6f 	movl   $0x6f6f7420,0x14(%eax)
 80496ec:	c7 40 18 20 6c 61 72 	movl   $0x72616c20,0x18(%eax)
 80496f3:	c7 40 1c 67 65 2e 20 	movl   $0x202e6567,0x1c(%eax)
 80496fa:	c7 40 20 49 6e 63 72 	movl   $0x72636e49,0x20(%eax)
 8049701:	c7 40 24 65 61 73 65 	movl   $0x65736165,0x24(%eax)
 8049708:	c7 40 28 20 53 55 42 	movl   $0x42555320,0x28(%eax)
 804970f:	c7 40 2c 4d 49 54 52 	movl   $0x5254494d,0x2c(%eax)
 8049716:	c7 40 30 5f 4d 41 58 	movl   $0x58414d5f,0x30(%eax)
 804971d:	c7 40 34 42 55 46 00 	movl   $0x465542,0x34(%eax)
 8049724:	83 ec 0c             	sub    $0xc,%esp
 8049727:	ff 74 24 14          	pushl  0x14(%esp)
 804972b:	e8 50 f1 ff ff       	call   8048880 <close@plt>
 8049730:	83 c4 10             	add    $0x10,%esp
 8049733:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049738:	e9 11 05 00 00       	jmp    8049c4e <submitr+0x7e2>
 804973d:	8d 94 24 24 40 00 00 	lea    0x4024(%esp),%edx
 8049744:	b9 00 08 00 00       	mov    $0x800,%ecx
 8049749:	b8 00 00 00 00       	mov    $0x0,%eax
 804974e:	89 d7                	mov    %edx,%edi
 8049750:	f3 ab                	rep stos %eax,%es:(%edi)
 8049752:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049757:	89 df                	mov    %ebx,%edi
 8049759:	f2 ae                	repnz scas %es:(%edi),%al
 804975b:	f7 d1                	not    %ecx
 804975d:	89 ce                	mov    %ecx,%esi
 804975f:	83 ee 01             	sub    $0x1,%esi
 8049762:	0f 84 86 04 00 00    	je     8049bee <submitr+0x782>
 8049768:	89 d5                	mov    %edx,%ebp
 804976a:	bf d9 ff 00 00       	mov    $0xffd9,%edi
 804976f:	0f b6 13             	movzbl (%ebx),%edx
 8049772:	8d 4a d6             	lea    -0x2a(%edx),%ecx
 8049775:	b8 01 00 00 00       	mov    $0x1,%eax
 804977a:	80 f9 0f             	cmp    $0xf,%cl
 804977d:	77 0a                	ja     8049789 <submitr+0x31d>
 804977f:	89 f8                	mov    %edi,%eax
 8049781:	d3 e8                	shr    %cl,%eax
 8049783:	83 f0 01             	xor    $0x1,%eax
 8049786:	83 e0 01             	and    $0x1,%eax
 8049789:	80 fa 5f             	cmp    $0x5f,%dl
 804978c:	0f 94 c1             	sete   %cl
 804978f:	38 c1                	cmp    %al,%cl
 8049791:	73 0c                	jae    804979f <submitr+0x333>
 8049793:	89 d0                	mov    %edx,%eax
 8049795:	83 e0 df             	and    $0xffffffdf,%eax
 8049798:	83 e8 41             	sub    $0x41,%eax
 804979b:	3c 19                	cmp    $0x19,%al
 804979d:	77 08                	ja     80497a7 <submitr+0x33b>
 804979f:	88 55 00             	mov    %dl,0x0(%ebp)
 80497a2:	8d 6d 01             	lea    0x1(%ebp),%ebp
 80497a5:	eb 52                	jmp    80497f9 <submitr+0x38d>
 80497a7:	80 fa 20             	cmp    $0x20,%dl
 80497aa:	75 09                	jne    80497b5 <submitr+0x349>
 80497ac:	c6 45 00 2b          	movb   $0x2b,0x0(%ebp)
 80497b0:	8d 6d 01             	lea    0x1(%ebp),%ebp
 80497b3:	eb 44                	jmp    80497f9 <submitr+0x38d>
 80497b5:	8d 42 e0             	lea    -0x20(%edx),%eax
 80497b8:	3c 5f                	cmp    $0x5f,%al
 80497ba:	76 09                	jbe    80497c5 <submitr+0x359>
 80497bc:	80 fa 09             	cmp    $0x9,%dl
 80497bf:	0f 85 d6 03 00 00    	jne    8049b9b <submitr+0x72f>
 80497c5:	83 ec 04             	sub    $0x4,%esp
 80497c8:	0f b6 d2             	movzbl %dl,%edx
 80497cb:	52                   	push   %edx
 80497cc:	68 84 a5 04 08       	push   $0x804a584
 80497d1:	8d 44 24 24          	lea    0x24(%esp),%eax
 80497d5:	50                   	push   %eax
 80497d6:	e8 55 f0 ff ff       	call   8048830 <sprintf@plt>
 80497db:	0f b6 44 24 28       	movzbl 0x28(%esp),%eax
 80497e0:	88 45 00             	mov    %al,0x0(%ebp)
 80497e3:	0f b6 44 24 29       	movzbl 0x29(%esp),%eax
 80497e8:	88 45 01             	mov    %al,0x1(%ebp)
 80497eb:	0f b6 44 24 2a       	movzbl 0x2a(%esp),%eax
 80497f0:	88 45 02             	mov    %al,0x2(%ebp)
 80497f3:	83 c4 10             	add    $0x10,%esp
 80497f6:	8d 6d 03             	lea    0x3(%ebp),%ebp
 80497f9:	83 c3 01             	add    $0x1,%ebx
 80497fc:	83 ee 01             	sub    $0x1,%esi
 80497ff:	0f 85 6a ff ff ff    	jne    804976f <submitr+0x303>
 8049805:	e9 e4 03 00 00       	jmp    8049bee <submitr+0x782>
 804980a:	83 ec 04             	sub    $0x4,%esp
 804980d:	53                   	push   %ebx
 804980e:	56                   	push   %esi
 804980f:	55                   	push   %ebp
 8049810:	e8 cb ef ff ff       	call   80487e0 <write@plt>
 8049815:	83 c4 10             	add    $0x10,%esp
 8049818:	85 c0                	test   %eax,%eax
 804981a:	7f 0f                	jg     804982b <submitr+0x3bf>
 804981c:	e8 ff ef ff ff       	call   8048820 <__errno_location@plt>
 8049821:	83 38 04             	cmpl   $0x4,(%eax)
 8049824:	75 0f                	jne    8049835 <submitr+0x3c9>
 8049826:	b8 00 00 00 00       	mov    $0x0,%eax
 804982b:	01 c6                	add    %eax,%esi
 804982d:	29 c3                	sub    %eax,%ebx
 804982f:	75 d9                	jne    804980a <submitr+0x39e>
 8049831:	85 ff                	test   %edi,%edi
 8049833:	79 6c                	jns    80498a1 <submitr+0x435>
 8049835:	8b 84 24 78 a0 00 00 	mov    0xa078(%esp),%eax
 804983c:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049842:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049849:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049850:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049857:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 804985e:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049865:	c7 40 18 77 72 69 74 	movl   $0x74697277,0x18(%eax)
 804986c:	c7 40 1c 65 20 74 6f 	movl   $0x6f742065,0x1c(%eax)
 8049873:	c7 40 20 20 74 68 65 	movl   $0x65687420,0x20(%eax)
 804987a:	c7 40 24 20 73 65 72 	movl   $0x72657320,0x24(%eax)
 8049881:	c7 40 28 76 65 72 00 	movl   $0x726576,0x28(%eax)
 8049888:	83 ec 0c             	sub    $0xc,%esp
 804988b:	ff 74 24 14          	pushl  0x14(%esp)
 804988f:	e8 ec ef ff ff       	call   8048880 <close@plt>
 8049894:	83 c4 10             	add    $0x10,%esp
 8049897:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 804989c:	e9 ad 03 00 00       	jmp    8049c4e <submitr+0x7e2>
 80498a1:	8b 44 24 08          	mov    0x8(%esp),%eax
 80498a5:	89 84 24 24 80 00 00 	mov    %eax,0x8024(%esp)
 80498ac:	c7 84 24 28 80 00 00 	movl   $0x0,0x8028(%esp)
 80498b3:	00 00 00 00 
 80498b7:	8d 84 24 30 80 00 00 	lea    0x8030(%esp),%eax
 80498be:	89 84 24 2c 80 00 00 	mov    %eax,0x802c(%esp)
 80498c5:	b9 00 20 00 00       	mov    $0x2000,%ecx
 80498ca:	8d 94 24 24 60 00 00 	lea    0x6024(%esp),%edx
 80498d1:	8d 84 24 24 80 00 00 	lea    0x8024(%esp),%eax
 80498d8:	e8 dc fa ff ff       	call   80493b9 <rio_readlineb>
 80498dd:	85 c0                	test   %eax,%eax
 80498df:	0f 8f 80 00 00 00    	jg     8049965 <submitr+0x4f9>
 80498e5:	8b 84 24 78 a0 00 00 	mov    0xa078(%esp),%eax
 80498ec:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80498f2:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 80498f9:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049900:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049907:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 804990e:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049915:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 804991c:	c7 40 1c 20 66 69 72 	movl   $0x72696620,0x1c(%eax)
 8049923:	c7 40 20 73 74 20 68 	movl   $0x68207473,0x20(%eax)
 804992a:	c7 40 24 65 61 64 65 	movl   $0x65646165,0x24(%eax)
 8049931:	c7 40 28 72 20 66 72 	movl   $0x72662072,0x28(%eax)
 8049938:	c7 40 2c 6f 6d 20 73 	movl   $0x73206d6f,0x2c(%eax)
 804993f:	c7 40 30 65 72 76 65 	movl   $0x65767265,0x30(%eax)
 8049946:	66 c7 40 34 72 00    	movw   $0x72,0x34(%eax)
 804994c:	83 ec 0c             	sub    $0xc,%esp
 804994f:	ff 74 24 14          	pushl  0x14(%esp)
 8049953:	e8 28 ef ff ff       	call   8048880 <close@plt>
 8049958:	83 c4 10             	add    $0x10,%esp
 804995b:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049960:	e9 e9 02 00 00       	jmp    8049c4e <submitr+0x7e2>
 8049965:	83 ec 0c             	sub    $0xc,%esp
 8049968:	8d 44 24 2c          	lea    0x2c(%esp),%eax
 804996c:	50                   	push   %eax
 804996d:	8d 84 24 30 20 00 00 	lea    0x2030(%esp),%eax
 8049974:	50                   	push   %eax
 8049975:	8d 84 24 38 20 00 00 	lea    0x2038(%esp),%eax
 804997c:	50                   	push   %eax
 804997d:	68 8b a5 04 08       	push   $0x804a58b
 8049982:	8d 84 24 40 60 00 00 	lea    0x6040(%esp),%eax
 8049989:	50                   	push   %eax
 804998a:	e8 71 ee ff ff       	call   8048800 <__isoc99_sscanf@plt>
 804998f:	8b 84 24 40 20 00 00 	mov    0x2040(%esp),%eax
 8049996:	83 c4 20             	add    $0x20,%esp
 8049999:	3d c8 00 00 00       	cmp    $0xc8,%eax
 804999e:	0f 84 c3 00 00 00    	je     8049a67 <submitr+0x5fb>
 80499a4:	8d 54 24 20          	lea    0x20(%esp),%edx
 80499a8:	52                   	push   %edx
 80499a9:	50                   	push   %eax
 80499aa:	68 9c a4 04 08       	push   $0x804a49c
 80499af:	ff b4 24 84 a0 00 00 	pushl  0xa084(%esp)
 80499b6:	e8 75 ee ff ff       	call   8048830 <sprintf@plt>
 80499bb:	83 c4 04             	add    $0x4,%esp
 80499be:	ff 74 24 14          	pushl  0x14(%esp)
 80499c2:	e8 b9 ee ff ff       	call   8048880 <close@plt>
 80499c7:	83 c4 10             	add    $0x10,%esp
 80499ca:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 80499cf:	e9 7a 02 00 00       	jmp    8049c4e <submitr+0x7e2>
 80499d4:	b9 00 20 00 00       	mov    $0x2000,%ecx
 80499d9:	8d 94 24 24 60 00 00 	lea    0x6024(%esp),%edx
 80499e0:	8d 84 24 24 80 00 00 	lea    0x8024(%esp),%eax
 80499e7:	e8 cd f9 ff ff       	call   80493b9 <rio_readlineb>
 80499ec:	85 c0                	test   %eax,%eax
 80499ee:	7f 77                	jg     8049a67 <submitr+0x5fb>
 80499f0:	8b 84 24 78 a0 00 00 	mov    0xa078(%esp),%eax
 80499f7:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 80499fd:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049a04:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049a0b:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049a12:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049a19:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049a20:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 8049a27:	c7 40 1c 20 68 65 61 	movl   $0x61656820,0x1c(%eax)
 8049a2e:	c7 40 20 64 65 72 73 	movl   $0x73726564,0x20(%eax)
 8049a35:	c7 40 24 20 66 72 6f 	movl   $0x6f726620,0x24(%eax)
 8049a3c:	c7 40 28 6d 20 73 65 	movl   $0x6573206d,0x28(%eax)
 8049a43:	c7 40 2c 72 76 65 72 	movl   $0x72657672,0x2c(%eax)
 8049a4a:	c6 40 30 00          	movb   $0x0,0x30(%eax)
 8049a4e:	83 ec 0c             	sub    $0xc,%esp
 8049a51:	ff 74 24 14          	pushl  0x14(%esp)
 8049a55:	e8 26 ee ff ff       	call   8048880 <close@plt>
 8049a5a:	83 c4 10             	add    $0x10,%esp
 8049a5d:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049a62:	e9 e7 01 00 00       	jmp    8049c4e <submitr+0x7e2>
 8049a67:	80 bc 24 24 60 00 00 	cmpb   $0xd,0x6024(%esp)
 8049a6e:	0d 
 8049a6f:	0f 85 5f ff ff ff    	jne    80499d4 <submitr+0x568>
 8049a75:	80 bc 24 25 60 00 00 	cmpb   $0xa,0x6025(%esp)
 8049a7c:	0a 
 8049a7d:	0f 85 51 ff ff ff    	jne    80499d4 <submitr+0x568>
 8049a83:	80 bc 24 26 60 00 00 	cmpb   $0x0,0x6026(%esp)
 8049a8a:	00 
 8049a8b:	0f 85 43 ff ff ff    	jne    80499d4 <submitr+0x568>
 8049a91:	b9 00 20 00 00       	mov    $0x2000,%ecx
 8049a96:	8d 94 24 24 60 00 00 	lea    0x6024(%esp),%edx
 8049a9d:	8d 84 24 24 80 00 00 	lea    0x8024(%esp),%eax
 8049aa4:	e8 10 f9 ff ff       	call   80493b9 <rio_readlineb>
 8049aa9:	85 c0                	test   %eax,%eax
 8049aab:	0f 8f 81 00 00 00    	jg     8049b32 <submitr+0x6c6>
 8049ab1:	8b 84 24 78 a0 00 00 	mov    0xa078(%esp),%eax
 8049ab8:	c7 00 45 72 72 6f    	movl   $0x6f727245,(%eax)
 8049abe:	c7 40 04 72 3a 20 43 	movl   $0x43203a72,0x4(%eax)
 8049ac5:	c7 40 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%eax)
 8049acc:	c7 40 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%eax)
 8049ad3:	c7 40 10 61 62 6c 65 	movl   $0x656c6261,0x10(%eax)
 8049ada:	c7 40 14 20 74 6f 20 	movl   $0x206f7420,0x14(%eax)
 8049ae1:	c7 40 18 72 65 61 64 	movl   $0x64616572,0x18(%eax)
 8049ae8:	c7 40 1c 20 73 74 61 	movl   $0x61747320,0x1c(%eax)
 8049aef:	c7 40 20 74 75 73 20 	movl   $0x20737574,0x20(%eax)
 8049af6:	c7 40 24 6d 65 73 73 	movl   $0x7373656d,0x24(%eax)
 8049afd:	c7 40 28 61 67 65 20 	movl   $0x20656761,0x28(%eax)
 8049b04:	c7 40 2c 66 72 6f 6d 	movl   $0x6d6f7266,0x2c(%eax)
 8049b0b:	c7 40 30 20 73 65 72 	movl   $0x72657320,0x30(%eax)
 8049b12:	c7 40 34 76 65 72 00 	movl   $0x726576,0x34(%eax)
 8049b19:	83 ec 0c             	sub    $0xc,%esp
 8049b1c:	ff 74 24 14          	pushl  0x14(%esp)
 8049b20:	e8 5b ed ff ff       	call   8048880 <close@plt>
 8049b25:	83 c4 10             	add    $0x10,%esp
 8049b28:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049b2d:	e9 1c 01 00 00       	jmp    8049c4e <submitr+0x7e2>
 8049b32:	83 ec 08             	sub    $0x8,%esp
 8049b35:	8d 84 24 2c 60 00 00 	lea    0x602c(%esp),%eax
 8049b3c:	50                   	push   %eax
 8049b3d:	ff b4 24 84 a0 00 00 	pushl  0xa084(%esp)
 8049b44:	e8 17 ec ff ff       	call   8048760 <strcpy@plt>
 8049b49:	83 c4 04             	add    $0x4,%esp
 8049b4c:	ff 74 24 14          	pushl  0x14(%esp)
 8049b50:	e8 2b ed ff ff       	call   8048880 <close@plt>
 8049b55:	8b 84 24 88 a0 00 00 	mov    0xa088(%esp),%eax
 8049b5c:	0f b6 10             	movzbl (%eax),%edx
 8049b5f:	b8 4f 00 00 00       	mov    $0x4f,%eax
 8049b64:	83 c4 10             	add    $0x10,%esp
 8049b67:	29 d0                	sub    %edx,%eax
 8049b69:	75 21                	jne    8049b8c <submitr+0x720>
 8049b6b:	8b 84 24 78 a0 00 00 	mov    0xa078(%esp),%eax
 8049b72:	0f b6 50 01          	movzbl 0x1(%eax),%edx
 8049b76:	b8 4b 00 00 00       	mov    $0x4b,%eax
 8049b7b:	29 d0                	sub    %edx,%eax
 8049b7d:	75 0d                	jne    8049b8c <submitr+0x720>
 8049b7f:	8b 84 24 78 a0 00 00 	mov    0xa078(%esp),%eax
 8049b86:	0f b6 40 02          	movzbl 0x2(%eax),%eax
 8049b8a:	f7 d8                	neg    %eax
 8049b8c:	85 c0                	test   %eax,%eax
 8049b8e:	0f 95 c0             	setne  %al
 8049b91:	0f b6 c0             	movzbl %al,%eax
 8049b94:	f7 d8                	neg    %eax
 8049b96:	e9 b3 00 00 00       	jmp    8049c4e <submitr+0x7e2>
 8049b9b:	a1 cc a4 04 08       	mov    0x804a4cc,%eax
 8049ba0:	8b bc 24 78 a0 00 00 	mov    0xa078(%esp),%edi
 8049ba7:	89 07                	mov    %eax,(%edi)
 8049ba9:	a1 0b a5 04 08       	mov    0x804a50b,%eax
 8049bae:	8b bc 24 78 a0 00 00 	mov    0xa078(%esp),%edi
 8049bb5:	89 47 3f             	mov    %eax,0x3f(%edi)
 8049bb8:	8b 84 24 78 a0 00 00 	mov    0xa078(%esp),%eax
 8049bbf:	8d 78 04             	lea    0x4(%eax),%edi
 8049bc2:	83 e7 fc             	and    $0xfffffffc,%edi
 8049bc5:	29 f8                	sub    %edi,%eax
 8049bc7:	be cc a4 04 08       	mov    $0x804a4cc,%esi
 8049bcc:	29 c6                	sub    %eax,%esi
 8049bce:	83 c0 43             	add    $0x43,%eax
 8049bd1:	c1 e8 02             	shr    $0x2,%eax
 8049bd4:	89 c1                	mov    %eax,%ecx
 8049bd6:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
 8049bd8:	83 ec 0c             	sub    $0xc,%esp
 8049bdb:	ff 74 24 14          	pushl  0x14(%esp)
 8049bdf:	e8 9c ec ff ff       	call   8048880 <close@plt>
 8049be4:	83 c4 10             	add    $0x10,%esp
 8049be7:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049bec:	eb 60                	jmp    8049c4e <submitr+0x7e2>
 8049bee:	83 ec 08             	sub    $0x8,%esp
 8049bf1:	8d 84 24 2c 40 00 00 	lea    0x402c(%esp),%eax
 8049bf8:	50                   	push   %eax
 8049bf9:	ff b4 24 7c a0 00 00 	pushl  0xa07c(%esp)
 8049c00:	ff b4 24 7c a0 00 00 	pushl  0xa07c(%esp)
 8049c07:	ff b4 24 7c a0 00 00 	pushl  0xa07c(%esp)
 8049c0e:	68 10 a5 04 08       	push   $0x804a510
 8049c13:	8d bc 24 40 60 00 00 	lea    0x6040(%esp),%edi
 8049c1a:	57                   	push   %edi
 8049c1b:	e8 10 ec ff ff       	call   8048830 <sprintf@plt>
 8049c20:	b8 00 00 00 00       	mov    $0x0,%eax
 8049c25:	b9 ff ff ff ff       	mov    $0xffffffff,%ecx
 8049c2a:	f2 ae                	repnz scas %es:(%edi),%al
 8049c2c:	f7 d1                	not    %ecx
 8049c2e:	8d 79 ff             	lea    -0x1(%ecx),%edi
 8049c31:	83 c4 20             	add    $0x20,%esp
 8049c34:	89 fb                	mov    %edi,%ebx
 8049c36:	8d b4 24 24 60 00 00 	lea    0x6024(%esp),%esi
 8049c3d:	8b 6c 24 08          	mov    0x8(%esp),%ebp
 8049c41:	85 ff                	test   %edi,%edi
 8049c43:	0f 85 c1 fb ff ff    	jne    804980a <submitr+0x39e>
 8049c49:	e9 53 fc ff ff       	jmp    80498a1 <submitr+0x435>
 8049c4e:	81 c4 4c a0 00 00    	add    $0xa04c,%esp
 8049c54:	5b                   	pop    %ebx
 8049c55:	5e                   	pop    %esi
 8049c56:	5f                   	pop    %edi
 8049c57:	5d                   	pop    %ebp
 8049c58:	c3                   	ret    

/***********************************************************************/

08049c59 <init_timeout>:
 8049c59:	53                   	push   %ebx
 8049c5a:	83 ec 08             	sub    $0x8,%esp
 8049c5d:	8b 5c 24 10          	mov    0x10(%esp),%ebx
 8049c61:	85 db                	test   %ebx,%ebx
 8049c63:	74 24                	je     8049c89 <init_timeout+0x30>
 8049c65:	83 ec 08             	sub    $0x8,%esp
 8049c68:	68 98 93 04 08       	push   $0x8049398
 8049c6d:	6a 0e                	push   $0xe
 8049c6f:	e8 ac ea ff ff       	call   8048720 <signal@plt>
 8049c74:	85 db                	test   %ebx,%ebx
 8049c76:	b8 00 00 00 00       	mov    $0x0,%eax
 8049c7b:	0f 48 d8             	cmovs  %eax,%ebx
 8049c7e:	89 1c 24             	mov    %ebx,(%esp)
 8049c81:	e8 ba ea ff ff       	call   8048740 <alarm@plt>
 8049c86:	83 c4 10             	add    $0x10,%esp
 8049c89:	83 c4 08             	add    $0x8,%esp
 8049c8c:	5b                   	pop    %ebx
 8049c8d:	c3                   	ret    

08049c8e <init_driver>:
 8049c8e:	57                   	push   %edi
 8049c8f:	56                   	push   %esi
 8049c90:	53                   	push   %ebx
 8049c91:	83 ec 18             	sub    $0x18,%esp
 8049c94:	8b 74 24 28          	mov    0x28(%esp),%esi
 8049c98:	6a 01                	push   $0x1
 8049c9a:	6a 0d                	push   $0xd
 8049c9c:	e8 7f ea ff ff       	call   8048720 <signal@plt>
 8049ca1:	83 c4 08             	add    $0x8,%esp
 8049ca4:	6a 01                	push   $0x1
 8049ca6:	6a 1d                	push   $0x1d
 8049ca8:	e8 73 ea ff ff       	call   8048720 <signal@plt>
 8049cad:	83 c4 08             	add    $0x8,%esp
 8049cb0:	6a 01                	push   $0x1
 8049cb2:	6a 1d                	push   $0x1d
 8049cb4:	e8 67 ea ff ff       	call   8048720 <signal@plt>
 8049cb9:	83 c4 0c             	add    $0xc,%esp
 8049cbc:	6a 00                	push   $0x0
 8049cbe:	6a 01                	push   $0x1
 8049cc0:	6a 02                	push   $0x2
 8049cc2:	e8 79 eb ff ff       	call   8048840 <socket@plt>
 8049cc7:	83 c4 10             	add    $0x10,%esp
 8049cca:	85 c0                	test   %eax,%eax
 8049ccc:	79 4e                	jns    8049d1c <init_driver+0x8e>
 8049cce:	c7 06 45 72 72 6f    	movl   $0x6f727245,(%esi)
 8049cd4:	c7 46 04 72 3a 20 43 	movl   $0x43203a72,0x4(%esi)
 8049cdb:	c7 46 08 6c 69 65 6e 	movl   $0x6e65696c,0x8(%esi)
 8049ce2:	c7 46 0c 74 20 75 6e 	movl   $0x6e752074,0xc(%esi)
 8049ce9:	c7 46 10 61 62 6c 65 	movl   $0x656c6261,0x10(%esi)
 8049cf0:	c7 46 14 20 74 6f 20 	movl   $0x206f7420,0x14(%esi)
 8049cf7:	c7 46 18 63 72 65 61 	movl   $0x61657263,0x18(%esi)
 8049cfe:	c7 46 1c 74 65 20 73 	movl   $0x73206574,0x1c(%esi)
 8049d05:	c7 46 20 6f 63 6b 65 	movl   $0x656b636f,0x20(%esi)
 8049d0c:	66 c7 46 24 74 00    	movw   $0x74,0x24(%esi)
 8049d12:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049d17:	e9 17 01 00 00       	jmp    8049e33 <init_driver+0x1a5>
 8049d1c:	89 c3                	mov    %eax,%ebx
 8049d1e:	83 ec 0c             	sub    $0xc,%esp
 8049d21:	68 9c a5 04 08       	push   $0x804a59c
 8049d26:	e8 25 eb ff ff       	call   8048850 <gethostbyname@plt>
 8049d2b:	83 c4 10             	add    $0x10,%esp
 8049d2e:	85 c0                	test   %eax,%eax
 8049d30:	75 6c                	jne    8049d9e <init_driver+0x110>
 8049d32:	c7 06 45 72 72 6f    	movl   $0x6f727245,(%esi)
 8049d38:	c7 46 04 72 3a 20 44 	movl   $0x44203a72,0x4(%esi)
 8049d3f:	c7 46 08 4e 53 20 69 	movl   $0x6920534e,0x8(%esi)
 8049d46:	c7 46 0c 73 20 75 6e 	movl   $0x6e752073,0xc(%esi)
 8049d4d:	c7 46 10 61 62 6c 65 	movl   $0x656c6261,0x10(%esi)
 8049d54:	c7 46 14 20 74 6f 20 	movl   $0x206f7420,0x14(%esi)
 8049d5b:	c7 46 18 72 65 73 6f 	movl   $0x6f736572,0x18(%esi)
 8049d62:	c7 46 1c 6c 76 65 20 	movl   $0x2065766c,0x1c(%esi)
 8049d69:	c7 46 20 73 65 72 76 	movl   $0x76726573,0x20(%esi)
 8049d70:	c7 46 24 65 72 20 61 	movl   $0x61207265,0x24(%esi)
 8049d77:	c7 46 28 64 64 72 65 	movl   $0x65726464,0x28(%esi)
 8049d7e:	66 c7 46 2c 73 73    	movw   $0x7373,0x2c(%esi)
 8049d84:	c6 46 2e 00          	movb   $0x0,0x2e(%esi)
 8049d88:	83 ec 0c             	sub    $0xc,%esp
 8049d8b:	53                   	push   %ebx
 8049d8c:	e8 ef ea ff ff       	call   8048880 <close@plt>
 8049d91:	83 c4 10             	add    $0x10,%esp
 8049d94:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049d99:	e9 95 00 00 00       	jmp    8049e33 <init_driver+0x1a5>
 8049d9e:	89 e7                	mov    %esp,%edi
 8049da0:	c7 04 24 00 00 00 00 	movl   $0x0,(%esp)
 8049da7:	c7 44 24 04 00 00 00 	movl   $0x0,0x4(%esp)
 8049dae:	00 
 8049daf:	c7 44 24 08 00 00 00 	movl   $0x0,0x8(%esp)
 8049db6:	00 
 8049db7:	c7 44 24 0c 00 00 00 	movl   $0x0,0xc(%esp)
 8049dbe:	00 
 8049dbf:	66 c7 04 24 02 00    	movw   $0x2,(%esp)
 8049dc5:	83 ec 04             	sub    $0x4,%esp
 8049dc8:	ff 70 0c             	pushl  0xc(%eax)
 8049dcb:	8d 54 24 0c          	lea    0xc(%esp),%edx
 8049dcf:	52                   	push   %edx
 8049dd0:	8b 40 10             	mov    0x10(%eax),%eax
 8049dd3:	ff 30                	pushl  (%eax)
 8049dd5:	e8 76 e9 ff ff       	call   8048750 <bcopy@plt>
 8049dda:	66 c7 44 24 12 3b 6e 	movw   $0x6e3b,0x12(%esp)
 8049de1:	83 c4 0c             	add    $0xc,%esp
 8049de4:	6a 10                	push   $0x10
 8049de6:	57                   	push   %edi
 8049de7:	53                   	push   %ebx
 8049de8:	e8 83 ea ff ff       	call   8048870 <connect@plt>
 8049ded:	83 c4 10             	add    $0x10,%esp
 8049df0:	85 c0                	test   %eax,%eax
 8049df2:	79 25                	jns    8049e19 <init_driver+0x18b>
 8049df4:	83 ec 04             	sub    $0x4,%esp
 8049df7:	68 9c a5 04 08       	push   $0x804a59c
 8049dfc:	68 5c a5 04 08       	push   $0x804a55c
 8049e01:	56                   	push   %esi
 8049e02:	e8 29 ea ff ff       	call   8048830 <sprintf@plt>
 8049e07:	89 1c 24             	mov    %ebx,(%esp)
 8049e0a:	e8 71 ea ff ff       	call   8048880 <close@plt>
 8049e0f:	83 c4 10             	add    $0x10,%esp
 8049e12:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8049e17:	eb 1a                	jmp    8049e33 <init_driver+0x1a5>
 8049e19:	83 ec 0c             	sub    $0xc,%esp
 8049e1c:	53                   	push   %ebx
 8049e1d:	e8 5e ea ff ff       	call   8048880 <close@plt>
 8049e22:	66 c7 06 4f 4b       	movw   $0x4b4f,(%esi)
 8049e27:	c6 46 02 00          	movb   $0x0,0x2(%esi)
 8049e2b:	83 c4 10             	add    $0x10,%esp
 8049e2e:	b8 00 00 00 00       	mov    $0x0,%eax
 8049e33:	83 c4 10             	add    $0x10,%esp
 8049e36:	5b                   	pop    %ebx
 8049e37:	5e                   	pop    %esi
 8049e38:	5f                   	pop    %edi
 8049e39:	c3                   	ret    

08049e3a <driver_post>:
 8049e3a:	53                   	push   %ebx
 8049e3b:	83 ec 08             	sub    $0x8,%esp
 8049e3e:	8b 44 24 10          	mov    0x10(%esp),%eax
 8049e42:	8b 5c 24 1c          	mov    0x1c(%esp),%ebx
 8049e46:	83 7c 24 18 00       	cmpl   $0x0,0x18(%esp)
 8049e4b:	74 24                	je     8049e71 <driver_post+0x37>
 8049e4d:	83 ec 08             	sub    $0x8,%esp
 8049e50:	ff 74 24 1c          	pushl  0x1c(%esp)
 8049e54:	68 b0 a5 04 08       	push   $0x804a5b0
 8049e59:	e8 92 e8 ff ff       	call   80486f0 <printf@plt>
 8049e5e:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049e63:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049e67:	83 c4 10             	add    $0x10,%esp
 8049e6a:	b8 00 00 00 00       	mov    $0x0,%eax
 8049e6f:	eb 3e                	jmp    8049eaf <driver_post+0x75>
 8049e71:	85 c0                	test   %eax,%eax
 8049e73:	74 2c                	je     8049ea1 <driver_post+0x67>
 8049e75:	80 38 00             	cmpb   $0x0,(%eax)
 8049e78:	74 27                	je     8049ea1 <driver_post+0x67>
 8049e7a:	83 ec 04             	sub    $0x4,%esp
 8049e7d:	53                   	push   %ebx
 8049e7e:	ff 74 24 1c          	pushl  0x1c(%esp)
 8049e82:	68 c7 a5 04 08       	push   $0x804a5c7
 8049e87:	50                   	push   %eax
 8049e88:	68 cb a5 04 08       	push   $0x804a5cb
 8049e8d:	68 6e 3b 00 00       	push   $0x3b6e
 8049e92:	68 9c a5 04 08       	push   $0x804a59c
 8049e97:	e8 d0 f5 ff ff       	call   804946c <submitr>
 8049e9c:	83 c4 20             	add    $0x20,%esp
 8049e9f:	eb 0e                	jmp    8049eaf <driver_post+0x75>
 8049ea1:	66 c7 03 4f 4b       	movw   $0x4b4f,(%ebx)
 8049ea6:	c6 43 02 00          	movb   $0x0,0x2(%ebx)
 8049eaa:	b8 00 00 00 00       	mov    $0x0,%eax
 8049eaf:	83 c4 08             	add    $0x8,%esp
 8049eb2:	5b                   	pop    %ebx
 8049eb3:	c3                   	ret    
 8049eb4:	66 90                	xchg   %ax,%ax
 8049eb6:	66 90                	xchg   %ax,%ax
 8049eb8:	66 90                	xchg   %ax,%ax
 8049eba:	66 90                	xchg   %ax,%ax
 8049ebc:	66 90                	xchg   %ax,%ax
 8049ebe:	66 90                	xchg   %ax,%ax

08049ec0 <__libc_csu_init>:
 8049ec0:	55                   	push   %ebp
 8049ec1:	57                   	push   %edi
 8049ec2:	56                   	push   %esi
 8049ec3:	53                   	push   %ebx
 8049ec4:	e8 07 ea ff ff       	call   80488d0 <__x86.get_pc_thunk.bx>
 8049ec9:	81 c3 2f 12 00 00    	add    $0x122f,%ebx
 8049ecf:	83 ec 0c             	sub    $0xc,%esp
 8049ed2:	8b 6c 24 20          	mov    0x20(%esp),%ebp
 8049ed6:	8d b3 0c ff ff ff    	lea    -0xf4(%ebx),%esi
 8049edc:	e8 c3 e7 ff ff       	call   80486a4 <_init>
 8049ee1:	8d 83 08 ff ff ff    	lea    -0xf8(%ebx),%eax
 8049ee7:	29 c6                	sub    %eax,%esi
 8049ee9:	c1 fe 02             	sar    $0x2,%esi
 8049eec:	85 f6                	test   %esi,%esi
 8049eee:	74 25                	je     8049f15 <__libc_csu_init+0x55>
 8049ef0:	31 ff                	xor    %edi,%edi
 8049ef2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8049ef8:	83 ec 04             	sub    $0x4,%esp
 8049efb:	ff 74 24 2c          	pushl  0x2c(%esp)
 8049eff:	ff 74 24 2c          	pushl  0x2c(%esp)
 8049f03:	55                   	push   %ebp
 8049f04:	ff 94 bb 08 ff ff ff 	call   *-0xf8(%ebx,%edi,4)
 8049f0b:	83 c7 01             	add    $0x1,%edi
 8049f0e:	83 c4 10             	add    $0x10,%esp
 8049f11:	39 f7                	cmp    %esi,%edi
 8049f13:	75 e3                	jne    8049ef8 <__libc_csu_init+0x38>
 8049f15:	83 c4 0c             	add    $0xc,%esp
 8049f18:	5b                   	pop    %ebx
 8049f19:	5e                   	pop    %esi
 8049f1a:	5f                   	pop    %edi
 8049f1b:	5d                   	pop    %ebp
 8049f1c:	c3                   	ret    
 8049f1d:	8d 76 00             	lea    0x0(%esi),%esi

08049f20 <__libc_csu_fini>:
 8049f20:	f3 c3                	repz ret 

Disassembly of section .fini:

08049f24 <_fini>:
 8049f24:	53                   	push   %ebx
 8049f25:	83 ec 08             	sub    $0x8,%esp
 8049f28:	e8 a3 e9 ff ff       	call   80488d0 <__x86.get_pc_thunk.bx>
 8049f2d:	81 c3 cb 11 00 00    	add    $0x11cb,%ebx
 8049f33:	83 c4 08             	add    $0x8,%esp
 8049f36:	5b                   	pop    %ebx
 8049f37:	c3                   	ret    
