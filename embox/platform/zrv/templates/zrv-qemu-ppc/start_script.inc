"smac_adm -R high_label -o low_label  -a r",
"smac_adm -R low_label  -o high_label -a w",
"smac_adm -R _  	-o smac_admin -a r",

"smac_adm -R confidentially -o unclassified  -a r",
"smac_adm -R confidentially -o service  -a r",
"smac_adm -R confidentially -o secret  -a r",

"smac_adm -R secret -o unclassified  -a r",
"smac_adm -R secret -o service  -a r",

"smac_adm -R service -o unclassified  -a r",

"login",

