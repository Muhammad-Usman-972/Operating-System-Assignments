echo "Press 1 to display permission of file"
echo "Press 2 to search string in file"
echo "Press 3 to add contents of all files in a file"
echo "Press 4 to check modified date of file"
echo "Enter choice : " 
read num
if [[ $num == '1' ]]; then
echo "___________________________________"
echo "Input a filename : "
read file
echo "Permission of " $file " is :"
permission=$(ls -l "$file.sh")
echo ${permission%% *}
octa_perm="0$(stat -c %a "$file.sh")"
invert_perm=$( printf "0%o" $(( octa_perm ^ 070 )) )
chmod "$invert_perm" "$file.sh"
echo "Updated Permission of " $file " is :"
permission=$(ls -l "$file.sh")
echo ${permission%% *}
echo "___________________________________"
elif [[ $num == '2' ]]; then
echo "___________________________________"
echo "Input a filename : "
read file
echo "Input a string : "
read str
grep "$str" "$file"
echo "___________________________________"
elif [[ $num == '3' ]]; then
echo "___________________________________"
echo "Enter number of lines to Copy : "
read copy
echo "creating dummy file"
touch "dummy1.txt"
echo "storing lines in dummy file"
num1=0 
for file in *.*
do
num2=$((num1%2))
if [ $k -eq 0 ]
then
echo "Storing First" $copy "Lines"
head -$copy "$file" >> "dummy.txt" 
else
echo "Storing Last" $copy "Lines"
tail -$copy "$file" >> "dummy.txt"
fi
num1=$((num1+1))
done
echo "___________________________________"
elif [[ $num == '4' ]]; then 
echo "___________________________________"
echo "Enter filename : "
read file_name
echo "Last time when file was updated is : "
echo $(date -r "$file")
num1=$(date -r "$file" +%s)                 
num2=$(date +%s)                                 
num3=$((num2-86400))                                
if [ $num1 -lt $num3 ]             
then
echo "File was updated long before 24 hours so updated time : "
touch "$file_name"
echo $(date -r "$file") 
else 
echo "File was updated with-in 24 hours so time : "
echo $(date -r "$file")
echo "___________________________________"
fi
else 
echo "invalid input"
fi
