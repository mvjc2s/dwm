#!/bin/sh

cat <<EOF | xmenu
[]= tile  0
><> floating	1
[M] monocle	2
TTT bstack	3
=== bstackhoriz 4
[@] spiral	5
[\\] dwindle	6
H[] deck	7
HHH grid	8
### nrowgrid	9
::: gaplessgrid 10
--- horizgrid 11
|M| centeredmaster	12
>M> centeredfloatingmaster	13
EOF
