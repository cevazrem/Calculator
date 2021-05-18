# Calculator

Simple calculator using recursion

Grammar
L -> C {+ C}
C -> A {- A}
A -> M {* M}
M -> K {/ K}
K -> num | (L)
