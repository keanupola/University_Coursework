# PAY ATTENTION TO ORDER
# Replace phone numbers with their respective format
s/[0-9]{3}-[0-9]{3}-[0-9]{4}/###-###-####/g
s/[0-9]{3}-[0-9]{4}/###-####/g
s/([0-9]{3}) [0-9]{3}-[0-9]{4}/(###) ###-####/g

# Remove strings between existing '%' characters
s/%[^%]*%//g

# Replace Social Security numbers with %%%-%%-%%%%
s/[0-9]{3}-[0-9]{2}-[0-9]{4}/%%%-%%-%%%%/g

# Insert the lines above the lines starting with '* '
/^\* /i\
\
* ATTENTION *\

# Convert DD/MM/YYYY to YYYY-MM-DD, use grouping to "catch" for backreferences
s|([0-9]{1,2})/([0-9]{1,2})/([0-9]{4})|\3-\2-\1|g
