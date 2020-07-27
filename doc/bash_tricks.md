Create directories with the same names as those present in another
directory.

	for dir in ../svd/*/; do dir=$(echo $dir | cut -d'/' -f3-); mkdir $dir; done

Basic sed. -i for "in place" (-i".bak" to backup the original files). -e
for the "script" (just an expression in this case, -f for a file).

	sed -i -e "s/Coder/Coder4Svd/g" coding4svd.py ecg4svd.py

Basic recursive file find.

	find . -name "*.py"

Find for files only (-type f; -type -d for directories)

	find . -name "*.py" -type f
