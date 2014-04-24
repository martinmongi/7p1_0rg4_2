global trie_crear
global nodo_crear
global insertar_nodo_en_nivel
global trie_agregar_palabra
global trie_construir
global trie_borrar
global trie_imprimir
global buscar_palabra
global palabras_con_prefijo
global trie_pesar
global nodo_buscar
global normalizar
global nodo_prefijo

extern malloc
extern free
extern fopen
extern fprintf
extern fclose
extern fscanf
extern palabras
extern lista_borrar

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
%define offset_sig_lnodo 8

%define NULL 0

%define FALSE 0
%define TRUE 1

section .rodata

section .data

append: DB 'a', 0
read: DB 'r', 0
vacio: DB '<vacio>', 0
lf: DB 10, 0
string: times 1024 DB '\0'
formato_string_out: DB '%s ', 0
formato_string_in: DB '%s', 0

section .text

; FUNCIONES OBLIGATORIAS. PUEDEN CREAR LAS FUNCIONES AUXILIARES QUE CREAN CONVENIENTES

;OK
trie_crear:
	PUSH RBP
	MOV RBP,RSP

	MOV RDI, size_trie ;parametro de malloc
	call malloc
	;RAX ya tiene el puntero del bloque de memoria pedido, no hace falta moverlo
	MOV qword [RAX + offset_raiz], NULL

	POP RBP
	RET

;OK
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

;OK
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

;OK
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

;OK
trie_agregar_palabra:
		PUSH RBP
		MOV RBP,RSP
		PUSH RBX
		PUSH R12
		PUSH R13
		PUSH R14

		MOV RBX, RDI			; N = RBX
		ADD RBX, offset_raiz
		MOV R12, 0				; I = R12
		XOR R13, R13			; H = R13
		MOV R14, RSI			; P = R14

	.recorrer:
		CMP byte [R14 + R12], NULL
		JE .salir
		MOV RDI, RBX
		MOV SIL, [R14 + R12]
		call insertar_nodo_en_nivel
		MOV R13, RAX
		MOV RBX, R13
		ADD RBX, offset_hijos
		INC R12
		JMP .recorrer

	.salir:
		MOV byte [R13 + offset_fin], TRUE

		POP R14
		POP R13
		POP R12
		POP RBX
		POP RBP
		RET

;OK
trie_construir:
		PUSH RBP
		MOV RBP, RSP
		PUSH RBX
		PUSH R12

		MOV R12, RDI		; Nombre_archivo = R12

		call trie_crear
		MOV RBX, RAX		; T = RBX

		MOV RDI, R12
		MOV RSI, read		; Nombre_archivo = RDI
		MOV RAX, 8
		call fopen
		MOV R12, RAX		;Puntero a archivo = R12

	 .ciclo:
	 	MOV RDI, R12
	 	MOV RSI, formato_string_in
	 	MOV RDX, string
	 	MOV RAX, 8
	 	call fscanf
	 	TEST EAX, EAX
	 	JS .salir
	 	MOV RDI, RBX
	 	MOV RSI, string
	 	call trie_agregar_palabra
	 	JMP .ciclo

	.salir:
		MOV RDI, R12
		MOV RAX, 8
		call fclose
		MOV RAX, RBX

		POP R12
		POP RBX
		POP RBP
		RET

;OK
trie_imprimir:
		PUSH RBP
		MOV RBP, RSP
		PUSH RBX
		PUSH R12
		PUSH R13
		PUSH R14

		MOV RBX, RDI 		; T =  RBX
		MOV R12, RSI 		; Nombre_archivo = R12

		MOV RDI, R12
		MOV RSI, append
		MOV RAX, 8
		call fopen
		MOV R12, RAX 		;Puntero a archivo F =  R12

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
		call reset_string
		MOV RDI, RBX
		ADD RDI, offset_raiz
		MOV RSI, string
		call palabras
		MOV R13, RAX		; LISTA L = R13
		MOV R14, [R13 + offset_prim]	;LSCAN = R14

	.ciclo:
		CMP R14, NULL
		JE .salir
		MOV RDI, R12
		MOV RSI, formato_string_out
		MOV RDX, [R14 + offset_valor]
		MOV RAX, 8
		call fprintf
		MOV R14, [R14 + offset_sig_lnodo]
		JMP .ciclo

	.salir:
		MOV RDI, R13
		call lista_borrar

	.cerrar:
		MOV RDI, R12
		MOV RSI, lf
		MOV RAX, 8
		call fprintf
		MOV RDI, R12
		MOV RAX, 8
		call fclose

		POP R14
		POP R13
		POP R12
		POP RBX
		POP RBP
		RET

;OK
buscar_palabra:
		PUSH RBP
		MOV RBP,RSP

		MOV RDI, [RDI + offset_raiz]
		;RSI esta perfecto ahi
		call nodo_prefijo
		CMP RAX, NULL
		JE .false
		CMP byte [RAX + offset_fin], 0
		JE .false

	.true:
		MOV RAX, 1
		POP RBP
		RET

	.false:
		MOV RAX, 0
		POP RBP
		RET

trie_pesar:
	; COMPLETAR AQUI EL CODIGO

palabras_con_prefijo:
	; COMPLETAR AQUI EL CODIGO

;OK
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

;OK
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

;OK
nodo_buscar:
		PUSH RBP
		MOV RBP,RSP

	.buscar:
		CMP RDI, NULL
		JE .salir
		CMP [RDI + offset_c], SIL
		JE .salir
		MOV RDI, [RDI + offset_sig]
		JMP .buscar

	.salir:
		MOV RAX, RDI
		POP RBP
		RET

;OK
nodo_prefijo:
		PUSH RBP
		MOV RBP,RSP
		PUSH RBX
		PUSH R12
		PUSH R13

		MOV RBX, RDI	;N = RBX
		MOV R12, RSI	;P = R12
		MOV R13, 0		;I = R13

	.recorrer:
		CMP RBX, NULL
		JE .salir
		CMP byte [R12 + R13 + 1], NULL
		JE .salir

		MOV RDI, RBX
		MOV SIL, [R12 + R13]
		call nodo_buscar
		MOV RBX, [RBX + offset_hijos]
		INC R13
		JMP .recorrer

	.salir:
		MOV RDI, RBX
		MOV SIL, [R12 + R13]
		call nodo_buscar
		;RAX ya tiene lo que hay que devolver, entonces ni lo trie_no_vacio

		POP R13
		POP R12
		POP RBX
		POP RBP
		RET

;OK
reset_string:
		PUSH RBP
		MOV RBP,RSP
		MOV RAX, 0

	.ciclo:
		MOV byte [string + RAX], 0
		INC RAX
		CMP RAX, 1024
		JE .salir
		JMP .ciclo

	.salir:
		POP RBP
		RET