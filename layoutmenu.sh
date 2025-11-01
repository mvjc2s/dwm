#!/bin/sh

cat <<EOF | xmenu
[]= tile (Mod+w, t)	0
><> floating (Mod+w, f)	1
[M] monocle (Mod+w, m)	2
TTT bstack (Mod+w, b)	3
=== bstackhoriz (Mod+w, Sft+b)	4
[@] spiral (Mod+w, s)	5
[\\] dwindle (Mod+w, d)	6
H[] deck (Mod+w, Sft+d)	7
HHH grid (Mod+w, g)	8
### nrowgrid (Mod+w, Sft+g)	9
::: gaplessgrid (Mod+w, Ctl+g)	10
--- horizgrid (Mod+w, h)	11
|M| centeredmaster (Mod+w, c)	12
>M> centeredfloatingmaster (Mod+w, Sft+c)	13
EOF
