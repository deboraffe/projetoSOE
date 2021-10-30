#!/bin/bash

nome_imagem="foto.jpg"
email_from="brenotwf@gmail.com"
passw_from="pixu2010"
email_to="brenotwf@gmail.com"
servidor_envio="smtp://smtp.gmail.com:587"
criptografia="--ssl"
email_subject="ATENÇÃO"
echo "From: <$email_from>" > email.txt
echo "To: <$email_to>" >> email.txt
echo Subject: $email_subject >> email.txt
echo Date: $(date) >> email.txt
echo Content-Type: multipart/mixed\; boundary=corpo_msg >> email.txt
echo >> email.txt
echo --corpo_msg >> email.txt
echo Content-Type: text/plain\; charset=UTF-8 >> email.txt
echo >> email.txt
echo $(cat temperatura.txt) >> email.txt
echo >> email.txt
echo --corpo_msg >> email.txt
echo Content-Type: image/png\; name=\"$nome_imagem\" >> email.txt
echo Content-Transfer-Encoding: base64 >> email.txt
echo Content-Disposition: attachment; filename=\"$nome_imagem\" >> email.txt
echo >> email.txt
cat $nome_imagem | base64 >> email.txt
echo --corpo_msg-- >> email.txt
curl -u $email_from:$passw_from -n -v --mail-from $email_from --mail-rcpt $email_to --url $servidor_envio $criptografia -T email.txt

