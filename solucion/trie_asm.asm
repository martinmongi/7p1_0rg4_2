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

extern malloc
extern free
extern fopen
extern fprintf
extern fclose

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

	;RDI ya tiene el puntero de bloque a hacer free, no hace falta moverlo
	call free

	POP RBP
	RET

nodo_crear:
	; COMPLETAR AQUI EL CODIGO

insertar_nodo_en_nivel:
	; COMPLETAR AQUI EL CODIGO

trie_agregar_palabra:
	; COMPLETAR AQUI EL CODIGO

trie_construir:
	; COMPLETAR AQUI EL CODIGO

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
		JMP .cerrar

	.trie_vacio:
		MOV RDI, R12
		MOV RSI, vacio
		MOV RAX, 8
		call fprintf

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

