Create directories with the same names as those present in another
directory.

	for dir in ../svd/*/; do dir=$(echo $dir | cut -d'/' -f3-); mkdir $dir; done
