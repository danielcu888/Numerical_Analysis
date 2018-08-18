#! /bin/bash -

OUTPUT_DIR=${PWD}/ex3_output

if [ ! -d ${OUTPUT_DIR} ]
then
    mkdir ${OUTPUT_DIR}
fi

j=1
for i in `seq 1 0.1 4`
do
    ${PWD}/ex3 ${i} > ${OUTPUT_DIR}/o${j}.txt
    ((j++))
done

for f in `find ${OUTPUT_DIR}`
do
    if [ -f ${f} ]
    then
        cat $f | sed -e s/"Term #"//g | grep -v "ex3" > ${f}2
        mv ${f}2 ${f}
    fi
done

exit $?