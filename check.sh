# Source - https://stackoverflow.com/a/71400086
# Posted by polkas, modified by community. See post 'Timeline' for change history
# Retrieved 2026-06-04, License - CC BY-SA 4.0

R CMD build . && R CMD check $(ls -t . | head -n1)
