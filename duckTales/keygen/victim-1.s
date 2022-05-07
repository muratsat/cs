
victim-1:     file format elf32-i386


Disassembly of section .init:

08048324 <_init>:
 8048324:	53                   	push   %ebx
 8048325:	83 ec 08             	sub    $0x8,%esp
 8048328:	e8 00 00 00 00       	call   804832d <_init+0x9>
 804832d:	5b                   	pop    %ebx
 804832e:	81 c3 c7 1c 00 00    	add    $0x1cc7,%ebx
 8048334:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 804833a:	85 c0                	test   %eax,%eax
 804833c:	74 05                	je     8048343 <_init+0x1f>
 804833e:	e8 21 00 00 00       	call   8048364 <__gmon_start__@plt>
 8048343:	e8 08 01 00 00       	call   8048450 <frame_dummy>
 8048348:	e8 03 02 00 00       	call   8048550 <__do_global_ctors_aux>
 804834d:	83 c4 08             	add    $0x8,%esp
 8048350:	5b                   	pop    %ebx
 8048351:	c3                   	ret    

Disassembly of section .plt:

08048354 <.plt>:
 8048354:	ff 35 f8 9f 04 08    	pushl  0x8049ff8
 804835a:	ff 25 fc 9f 04 08    	jmp    *0x8049ffc
 8048360:	00 00                	add    %al,(%eax)
	...

08048364 <__gmon_start__@plt>:
 8048364:	ff 25 00 a0 04 08    	jmp    *0x804a000
 804836a:	68 00 00 00 00       	push   $0x0
 804836f:	e9 e0 ff ff ff       	jmp    8048354 <.plt>

08048374 <__libc_start_main@plt>:
 8048374:	ff 25 04 a0 04 08    	jmp    *0x804a004
 804837a:	68 08 00 00 00       	push   $0x8
 804837f:	e9 d0 ff ff ff       	jmp    8048354 <.plt>

08048384 <scanf@plt>:
 8048384:	ff 25 08 a0 04 08    	jmp    *0x804a008
 804838a:	68 10 00 00 00       	push   $0x10
 804838f:	e9 c0 ff ff ff       	jmp    8048354 <.plt>

08048394 <printf@plt>:
 8048394:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 804839a:	68 18 00 00 00       	push   $0x18
 804839f:	e9 b0 ff ff ff       	jmp    8048354 <.plt>

080483a4 <exit@plt>:
 80483a4:	ff 25 10 a0 04 08    	jmp    *0x804a010
 80483aa:	68 20 00 00 00       	push   $0x20
 80483af:	e9 a0 ff ff ff       	jmp    8048354 <.plt>

Disassembly of section .text:

080483c0 <_start>:
 80483c0:	31 ed                	xor    %ebp,%ebp
 80483c2:	5e                   	pop    %esi
 80483c3:	89 e1                	mov    %esp,%ecx
 80483c5:	83 e4 f0             	and    $0xfffffff0,%esp
 80483c8:	50                   	push   %eax
 80483c9:	54                   	push   %esp
 80483ca:	52                   	push   %edx
 80483cb:	68 40 85 04 08       	push   $0x8048540
 80483d0:	68 d0 84 04 08       	push   $0x80484d0
 80483d5:	51                   	push   %ecx
 80483d6:	56                   	push   %esi
 80483d7:	68 80 84 04 08       	push   $0x8048480
 80483dc:	e8 93 ff ff ff       	call   8048374 <__libc_start_main@plt>
 80483e1:	f4                   	hlt    
 80483e2:	90                   	nop
 80483e3:	90                   	nop
 80483e4:	90                   	nop
 80483e5:	90                   	nop
 80483e6:	90                   	nop
 80483e7:	90                   	nop
 80483e8:	90                   	nop
 80483e9:	90                   	nop
 80483ea:	90                   	nop
 80483eb:	90                   	nop
 80483ec:	90                   	nop
 80483ed:	90                   	nop
 80483ee:	90                   	nop
 80483ef:	90                   	nop

080483f0 <__do_global_dtors_aux>:
 80483f0:	55                   	push   %ebp
 80483f1:	89 e5                	mov    %esp,%ebp
 80483f3:	53                   	push   %ebx
 80483f4:	83 ec 04             	sub    $0x4,%esp
 80483f7:	80 3d 3c a0 04 08 00 	cmpb   $0x0,0x804a03c
 80483fe:	75 3f                	jne    804843f <__do_global_dtors_aux+0x4f>
 8048400:	a1 40 a0 04 08       	mov    0x804a040,%eax
 8048405:	bb 18 9f 04 08       	mov    $0x8049f18,%ebx
 804840a:	81 eb 14 9f 04 08    	sub    $0x8049f14,%ebx
 8048410:	c1 fb 02             	sar    $0x2,%ebx
 8048413:	83 eb 01             	sub    $0x1,%ebx
 8048416:	39 d8                	cmp    %ebx,%eax
 8048418:	73 1e                	jae    8048438 <__do_global_dtors_aux+0x48>
 804841a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048420:	83 c0 01             	add    $0x1,%eax
 8048423:	a3 40 a0 04 08       	mov    %eax,0x804a040
 8048428:	ff 14 85 14 9f 04 08 	call   *0x8049f14(,%eax,4)
 804842f:	a1 40 a0 04 08       	mov    0x804a040,%eax
 8048434:	39 d8                	cmp    %ebx,%eax
 8048436:	72 e8                	jb     8048420 <__do_global_dtors_aux+0x30>
 8048438:	c6 05 3c a0 04 08 01 	movb   $0x1,0x804a03c
 804843f:	83 c4 04             	add    $0x4,%esp
 8048442:	5b                   	pop    %ebx
 8048443:	5d                   	pop    %ebp
 8048444:	c3                   	ret    
 8048445:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048449:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048450 <frame_dummy>:
 8048450:	55                   	push   %ebp
 8048451:	89 e5                	mov    %esp,%ebp
 8048453:	83 ec 18             	sub    $0x18,%esp
 8048456:	a1 1c 9f 04 08       	mov    0x8049f1c,%eax
 804845b:	85 c0                	test   %eax,%eax
 804845d:	74 12                	je     8048471 <frame_dummy+0x21>
 804845f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048464:	85 c0                	test   %eax,%eax
 8048466:	74 09                	je     8048471 <frame_dummy+0x21>
 8048468:	c7 04 24 1c 9f 04 08 	movl   $0x8049f1c,(%esp)
 804846f:	ff d0                	call   *%eax
 8048471:	c9                   	leave  
 8048472:	c3                   	ret    
 8048473:	90                   	nop
 8048474:	90                   	nop
 8048475:	90                   	nop
 8048476:	90                   	nop
 8048477:	90                   	nop
 8048478:	90                   	nop
 8048479:	90                   	nop
 804847a:	90                   	nop
 804847b:	90                   	nop
 804847c:	90                   	nop
 804847d:	90                   	nop
 804847e:	90                   	nop
 804847f:	90                   	nop

08048480 <main>:
 8048480:	68 44 a0 04 08       	push   $0x804a044
 8048485:	68 1c a0 04 08       	push   $0x804a01c
 804848a:	e8 f5 fe ff ff       	call   8048384 <scanf@plt>
 804848f:	68 48 a0 04 08       	push   $0x804a048
 8048494:	68 1c a0 04 08       	push   $0x804a01c
 8048499:	e8 e6 fe ff ff       	call   8048384 <scanf@plt>
 804849e:	a1 44 a0 04 08       	mov    0x804a044,%eax
 80484a3:	8b 1d 48 a0 04 08    	mov    0x804a048,%ebx
 80484a9:	29 d8                	sub    %ebx,%eax
 80484ab:	3d 95 88 01 00       	cmp    $0x18895,%eax
 80484b0:	75 11                	jne    80484c3 <wc>
 80484b2:	68 2b a0 04 08       	push   $0x804a02b
 80484b7:	e8 d8 fe ff ff       	call   8048394 <printf@plt>
 80484bc:	6a 00                	push   $0x0
 80484be:	e8 e1 fe ff ff       	call   80483a4 <exit@plt>

080484c3 <wc>:
 80484c3:	68 1f a0 04 08       	push   $0x804a01f
 80484c8:	e8 c7 fe ff ff       	call   8048394 <printf@plt>
 80484cd:	eb b1                	jmp    8048480 <main>
 80484cf:	90                   	nop

080484d0 <__libc_csu_init>:
 80484d0:	55                   	push   %ebp
 80484d1:	57                   	push   %edi
 80484d2:	56                   	push   %esi
 80484d3:	53                   	push   %ebx
 80484d4:	e8 69 00 00 00       	call   8048542 <__i686.get_pc_thunk.bx>
 80484d9:	81 c3 1b 1b 00 00    	add    $0x1b1b,%ebx
 80484df:	83 ec 1c             	sub    $0x1c,%esp
 80484e2:	8b 6c 24 30          	mov    0x30(%esp),%ebp
 80484e6:	8d bb 18 ff ff ff    	lea    -0xe8(%ebx),%edi
 80484ec:	e8 33 fe ff ff       	call   8048324 <_init>
 80484f1:	8d 83 18 ff ff ff    	lea    -0xe8(%ebx),%eax
 80484f7:	29 c7                	sub    %eax,%edi
 80484f9:	c1 ff 02             	sar    $0x2,%edi
 80484fc:	85 ff                	test   %edi,%edi
 80484fe:	74 29                	je     8048529 <__libc_csu_init+0x59>
 8048500:	31 f6                	xor    %esi,%esi
 8048502:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048508:	8b 44 24 38          	mov    0x38(%esp),%eax
 804850c:	89 2c 24             	mov    %ebp,(%esp)
 804850f:	89 44 24 08          	mov    %eax,0x8(%esp)
 8048513:	8b 44 24 34          	mov    0x34(%esp),%eax
 8048517:	89 44 24 04          	mov    %eax,0x4(%esp)
 804851b:	ff 94 b3 18 ff ff ff 	call   *-0xe8(%ebx,%esi,4)
 8048522:	83 c6 01             	add    $0x1,%esi
 8048525:	39 fe                	cmp    %edi,%esi
 8048527:	75 df                	jne    8048508 <__libc_csu_init+0x38>
 8048529:	83 c4 1c             	add    $0x1c,%esp
 804852c:	5b                   	pop    %ebx
 804852d:	5e                   	pop    %esi
 804852e:	5f                   	pop    %edi
 804852f:	5d                   	pop    %ebp
 8048530:	c3                   	ret    
 8048531:	eb 0d                	jmp    8048540 <__libc_csu_fini>
 8048533:	90                   	nop
 8048534:	90                   	nop
 8048535:	90                   	nop
 8048536:	90                   	nop
 8048537:	90                   	nop
 8048538:	90                   	nop
 8048539:	90                   	nop
 804853a:	90                   	nop
 804853b:	90                   	nop
 804853c:	90                   	nop
 804853d:	90                   	nop
 804853e:	90                   	nop
 804853f:	90                   	nop

08048540 <__libc_csu_fini>:
 8048540:	f3 c3                	repz ret 

08048542 <__i686.get_pc_thunk.bx>:
 8048542:	8b 1c 24             	mov    (%esp),%ebx
 8048545:	c3                   	ret    
 8048546:	90                   	nop
 8048547:	90                   	nop
 8048548:	90                   	nop
 8048549:	90                   	nop
 804854a:	90                   	nop
 804854b:	90                   	nop
 804854c:	90                   	nop
 804854d:	90                   	nop
 804854e:	90                   	nop
 804854f:	90                   	nop

08048550 <__do_global_ctors_aux>:
 8048550:	55                   	push   %ebp
 8048551:	89 e5                	mov    %esp,%ebp
 8048553:	53                   	push   %ebx
 8048554:	83 ec 04             	sub    $0x4,%esp
 8048557:	a1 0c 9f 04 08       	mov    0x8049f0c,%eax
 804855c:	83 f8 ff             	cmp    $0xffffffff,%eax
 804855f:	74 13                	je     8048574 <__do_global_ctors_aux+0x24>
 8048561:	bb 0c 9f 04 08       	mov    $0x8049f0c,%ebx
 8048566:	66 90                	xchg   %ax,%ax
 8048568:	83 eb 04             	sub    $0x4,%ebx
 804856b:	ff d0                	call   *%eax
 804856d:	8b 03                	mov    (%ebx),%eax
 804856f:	83 f8 ff             	cmp    $0xffffffff,%eax
 8048572:	75 f4                	jne    8048568 <__do_global_ctors_aux+0x18>
 8048574:	83 c4 04             	add    $0x4,%esp
 8048577:	5b                   	pop    %ebx
 8048578:	5d                   	pop    %ebp
 8048579:	c3                   	ret    
 804857a:	90                   	nop
 804857b:	90                   	nop

Disassembly of section .fini:

0804857c <_fini>:
 804857c:	53                   	push   %ebx
 804857d:	83 ec 08             	sub    $0x8,%esp
 8048580:	e8 00 00 00 00       	call   8048585 <_fini+0x9>
 8048585:	5b                   	pop    %ebx
 8048586:	81 c3 6f 1a 00 00    	add    $0x1a6f,%ebx
 804858c:	e8 5f fe ff ff       	call   80483f0 <__do_global_dtors_aux>
 8048591:	83 c4 08             	add    $0x8,%esp
 8048594:	5b                   	pop    %ebx
 8048595:	c3                   	ret    
