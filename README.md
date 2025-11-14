Lembrete de Pausa – ESP32

Este projeto implementa um lembrete automático de pausas utilizando ESP32, leitura de botão como sensor, buzzer como atuador e comunicação HTTP. A solução foi desenvolvida para incentivar pausas regulares durante atividades de trabalho, promovendo saúde e bem-estar.

# Problema e Solução.

O problema abordado é a falta de pausas durante longos períodos de trabalho, especialmente em tarefas digitais. O sistema monitora o tempo de atividade e emite um alerta sonoro após um intervalo definido. O usuário confirma a pausa apertando o botão, e o sistema reinicia automaticamente a contagem e registra os eventos via HTTP. (No projeto, o tempo de pausa está em 20 segundos, com a finalidade de executar testes rápidos).

# Instruções de Uso.
	1.	Acesse o link da simulação Wokwi deste projeto.
	
	2.	Aguarde a conexão automática ao Wi-Fi de simulação.
	
	3.	O buzzer tocará quando o tempo de trabalho expirar.
	
	4.	Pressione o botão para confirmar a pausa e reiniciar o ciclo.
	
	5.	Os eventos “pausa_pendente” e “pausa_realizada” serão enviados via HTTP.

# Dependências.
		Biblioteca WiFi.h
		
		Biblioteca HTTPClient.h
		
		ESP32
		
		Botão (sensor digital)
		
		Buzzer (atuador)
		
		Fios de conexão

# Comunicação HTTP Utilizada.

O projeto utiliza requisições HTTP POST para registrar dois tipos de eventos:

		pausa_pendente — enviado quando o tempo de trabalho expira.
	
		pausa_realizada — enviado quando o usuário pressiona o botão.


# Link para a Simulação Wokwi.

https://wokwi.com/projects/447577532842668033

# Arquivos-Fonte.

Todos os arquivos necessários para a execução estão incluídos neste repositório:

		sketch.ino – código principal comentado.
		
		diagram.json – diagrama de circuito do Wokwi.
		
		wokwi-project.txt – metadados da simulação

# Imagens do circuito.

<img width="436" height="306" alt="image" src="https://github.com/user-attachments/assets/b87b209a-0100-4fc9-b419-bea4971bb605" />

# Impacto e relevância.

O projeto ajuda a garantir pausas regulares, algo essencial para evitar cansaço, desconforto físico e perda de foco durante longos períodos de trabalho. Ao automatizar esse lembrete, ele reduz a chance de a pessoa simplesmente esquecer de parar. Também mostra, de forma simples, como a IoT pode ser usada para melhorar bem-estar no dia a dia, reforçando a importância de pequenas soluções tecnológicas no futuro do trabalho.

		

	
