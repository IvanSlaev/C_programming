#!/bin/bash

echo "*** We are going to clean the following compiled data ***"
find . -name '.tmp_*' -type d
find . -name '.*' -type f
find . -name '*.ko' -type f
find . -name '*.o' -type f
find . -name '*.mod.*' -type f
find . -name 'modules.order' -type f
find . -name 'Module.symvers' -type f
read -r -p "Are you sure you want to permanently delete them? [y/N] " response
if [[ $response =~ ^([yY][eE][sS]|[yY])$ ]]
then
	find . -name '.tmp_*' -type d | xargs rm -rf
	find . -name '.*' -type f -delete
	find . -name '*.ko' -type f -delete
	find . -name '*.o' -type f -delete
	find . -name '*.mod.*' -type f -delete
	find . -name 'modules.order' -type f -delete
	find . -name 'Module.symvers' -type f -delete
	echo "*** All cleaned ***"
    else
	echo "*** Nothing cleaned ***"
fi

