awk -F ':' '{print $5 ":" $0}' $1 | sort | awk -F ':' '{for(i=2; i<=NF; i++) { printf "%s", $i; if(i < NF) printf ":"; } printf "\n"}'
