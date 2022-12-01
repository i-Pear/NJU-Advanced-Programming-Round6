index=1
g++ -std=c++11 -o main main.cpp ClassWithFixedSize.h Class.h Class.cpp

tmpfile="tmpout"
while [ $index -le 25 ]
do
  infile="in/input${index}.txt"
  outfile="out/output${index}.txt"
  tempfile="out/temp${index}.txt"
  ./main < ${infile} > ${tmpfile}
  diff --strip-trailing-cr ${outfile} ${tmpfile}
  if [ $? -eq 0 ];
  then
    echo "Accept $index"
  else
    echo "Failed $index"
  fi
  index=$(( $index + 1 ))
done
rm $tmpfile
rm main

echo 按任意键关闭
read -n 1
