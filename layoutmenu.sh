#!/bin/sh

cat <<EOF | xmenu
[]= tile (Mod+t)	0
><> floating (Mod+Sft+f)	1
[M] monocle (Mod+m)	2
TTT bstack (Mod+Sft+b)	3
=== bstackhoriz (Mod+Ctl+Sft+b)	4
[@] spiral (Mod+r)	5
[\\] dwindle (Mod+Sft+t)	6
H[] deck (Mod+Sft+d)	7
HHH grid (Mod+g)	8
### nrowgrid (Mod+Sft+g)	9
::: gaplessgrid (Mod+Ctl+Sft+g)	10
--- horizgrid (Mod+Sft+h)	11
|M| centeredmaster (Mod+c)	12
>M> centeredfloatingmaster (Mod+Sft+c)	13
EOF
