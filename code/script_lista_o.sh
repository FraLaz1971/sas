#!/bin/sh
echo "#!/bin/sh" >> create_lib.sh
echo creating lib$2.a
echo "ar rcs lib$2.a \\" >> create_lib.sh
 cat $1 |
while read -a line;
	#do -en echo "${line}";  sed -e "s/$/_newline_/g";
do  
	echo -en $line " " >> create_lib.sh
done
