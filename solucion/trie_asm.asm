global trie_crear
global nodo_crear
global insertar_nodo_en_nivel
; global trie_agregar_palabra
global trie_construir
global trie_borrar
global trie_imprimir
global buscar_palabra
global palabras_con_prefijo
global trie_pesar
global normalizar

extern malloc
extern free
extern fopen
extern fprintf
extern fclose
; extern nodo_borrar

; SE RECOMIENDA COMPLETAR LOS DEFINES CON LOS VALORES CORRECTOS
%define offset_sig 0
%define offset_hijos 8
%define offset_c 16
%define offset_fin 17

%define size_nodo 18

%define offset_raiz 0

%define size_trie 8

%define offset_prim 0

%define offset_valor 0
%define offset_sig_lnodo 1

%define NULL 0

%define FALSE 0
%define TRUE 1

section .rodata

section .data

append: DB 'a', 0
vacio: DB '<vacio>', 10, 0

section .text

; FUNCIONES OBLIGATORIAS. PUEDEN CREAR LAS FUNCIONES AUXILIARES QUE CREAN CONVENIENTES

trie_crear:
	PUSH RBP
	MOV RBP,RSP

	MOV RDI, size_trie ;parametro de malloc
	call malloc
	;RAX ya tiene el puntero del bloque de memoria pedido, no hace falta moverlo
	MOV qword [RAX + offset_raiz], NULL

	POP RBP
	RET

trie_borrar:
		PUSH RBP
		MOV RBP, RSP
		PUSH RBX ;

		MOV RBX, RDI ;Trie en RBX
		CMP qword [RDI + offset_raiz], NULL
		JE .trie_vacio
		MOV RDI, [RDI + offset_raiz]
		SUB RSP, 8
		call nodo_borrar
		ADD RSP, 8

	.trie_vacio:
		MOV RDI, RBX
		SUB RSP, 8
		call free
		ADD RSP, 8

		POP RBX
		POP RBP
		RET

nodo_crear:
		PUSH RBP
		MOV RBP,RSP
		PUSH RBX

		;c en DIL
		SUB RSP, 8
		call normalizar
		ADD RSP, 8
		MOV DIL, AL

		MOV BL, DIL ; char en BL
		MOV RDI, size_nodo ;parametro de malloc
		SUB RSP, 8
		call malloc
		ADD RSP, 8
		;RAX ya tiene el puntero del bloque de memoria pedido, no hace falta moverlo
		MOV qword [RAX + offset_hijos], NULL
		MOV qword [RAX + offset_sig], NULL
		MOV byte [RAX + offset_c], BL
		MOV byte [RAX + offset_fin], FALSE

		POP RBX
		POP RBP
		RET

insertar_nodo_en_nivel:
		PUSH RBP
		MOV RBP, RSP
		PUSH RBX
		PUSH R12

		MOV RBX, RDI ;nivel a RBX
		MOV R12B, SIL ;char a R12B

		MOV DIL, R12B
		call normalizar
		MOV R12B, AL

	.buscar:
		CMP qword[RBX], NULL
		JE .esta
		MOV RAX, [RBX]
		CMP [RAX + offset_c], R12B
		JGE .esta
		MOV RBX, RAX
		ADD RBX, offset_sig
		JMP .buscar

	.esta:
		CMP qword [RBX], NULL
		JE .no_esta
		MOV RAX, [RBX]
		CMP [RAX + offset_c], R12B
		JNE .no_esta

		POP R12
		POP RBX
		POP RBP
		RET

	.no_esta:
		MOV SIL, R12B
		call nodo_crear
		MOV R12, [RBX]
		MOV [RAX + offset_sig], R12
		MOV [RBX], RAX

		POP R12
		POP RBX
		POP RBP
		RET

trie_agregar_palabra:
	; COMPLETAR AQUI EL CODIGO

trie_construir:
	; COMPLETAR AQUI EL CODIGO

;FALTAAAAAAAAAA
trie_imprimir:
		PUSH RBP
		MOV RBP, RSP
		PUSH RBX
		PUSH R12

		MOV RBX, RDI ; Trie en RBX
		MOV R12, RSI ; Nombre_archivo en R12

		MOV RDI, R12
		MOV RSI, append
		MOV RAX, 8
		call fopen
		MOV R12, RAX ;Puntero a archivo en R12

		CMP qword [RBX + offset_raiz], NULL
		JE .trie_vacio
		JMP .trie_no_vacio

	.trie_vacio:
		MOV RDI, R12
		MOV RSI, vacio
		MOV RAX, 8
		call fprintf
		JMP .cerrar

	.trie_no_vacio:
		JMP .cerrar

	.cerrar:
		MOV RDI, R12
		MOV RAX, 8
		call fclose

		POP R12
		POP RBX
		POP RBP
		RET

buscar_palabra:
	; COMPLETAR AQUI EL CODIGO

trie_pesar:
	; COMPLETAR AQUI EL CODIGO

palabras_con_prefijo:
	; COMPLETAR AQUI EL CODIGO

nodo_borrar:
		PUSH RBP
		MOV RBP, RSP
		PUSH RBX

		MOV RBX, RDI ;nodo actual en RBX

		CMP RBX, NULL
		JE .salir

		SUB RSP, 8
		MOV RDI, [RBX + offset_hijos]
		call nodo_borrar
		MOV RDI, [RBX + offset_sig]
		call nodo_borrar
		MOV RDI, RBX
		call free
		ADD RSP, 8

	.salir:	
		POP RBX
		POP RBP
		RET

normalizar:
		PUSH RBP
		MOV RBP, RSP

		CMP DIL, '0'
		JL .a
		CMP DIL, '9'
		JLE .c
		CMP DIL, 'A'
		JL .a
		CMP DIL, 'Z'
		JLE .mayus
		CMP DIL, 'a'
		JL .a
		CMP DIL, 'z'
		JLE .c

	.a:
		MOV AL, 'a'
		JMP .salir

	.c:
		MOV AL, DIL
		JMP .salir

	.mayus:
		ADD DIL, 32
		MOV AL, BL
		JMP .salir

	.salir:
		POP RBP
		RET