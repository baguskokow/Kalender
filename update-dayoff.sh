MONTH=3
YEAR=0
curl -s "https://dayoffapi.vercel.app/api?month=$MONTH&year=$YEAR" | jq . > dayoff.json
