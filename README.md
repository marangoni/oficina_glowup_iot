# 🌱 GlowUp IoT: Ciência Delas — Expressões da Natureza

**Oficina maker de eletrônica, programação e Internet das Coisas (IoT)**  
**IFSP — Instituto Federal de Educação, Ciência e Tecnologia — Campus Hortolândia**

O **GlowUp IoT** é uma oficina prática em que as participantes aprendem a montar e programar o **GlowUP Plant**, um dispositivo que acompanha a umidade do solo de uma planta e comunica suas condições por meio de um display OLED e de alertas sonoros.

A proposta combina experimentação, criatividade e resolução de problemas: cada etapa apresenta orientações, atividades iniciais e desafios avançados opcionais.

## 🚀 Acessar a oficina

**Site (GitHub Pages):** https://marangoni.github.io/GlowUp-IoT-Oficina/

> O endereço ficará disponível depois que o repositório público for criado e o GitHub Pages for ativado na branch `main`, pasta `/ (root)`.

## 🧪 Etapas da oficina

| Etapa | Tema | O que será desenvolvido |
|:---:|---|---|
| 01 | Conhecendo o ESP32-C3 | Identificação da placa, configuração do Arduino IDE e primeiro programa. |
| 02 | Experimentando o ESP32-C3 | Montagens na protoboard, saídas digitais e alertas com buzzer. |
| 03 | Conectando os sensores | Leitura e interpretação das medições do sensor capacitivo de umidade do solo. |
| 04 | Dando vida à nossa planta! | Apresentação de informações e expressões gráficas no display OLED. |
| 05 | Construindo o GlowUP Plant | Integração do sensor, do OLED e do buzzer em um único sistema. |
| 06 | Personalizando o GlowUP Plant | Olhos animados com RoboEyes, expressões e personalização de alertas sonoros. |

As atividades podem ser acessadas a partir do `index.html`. A página `materiais.html` contém a lista de materiais da oficina.

## 🧰 Componentes principais

- **ESP32-C3 Super Mini** e cabo USB compatível;
- **Sensor capacitivo de umidade do solo**;
- **Display OLED SSD1306 de 0,96″, 128 × 64 pixels, interface I²C**;
- **Buzzer ativo**;
- Protoboard, jumpers, fonte de alimentação adequada e planta em vaso.

O OLED pode ser monocromático ou bicolor (amarelo/azul). No modelo bicolor, as faixas de cor são características físicas da tela, e não cores selecionadas pelo programa.

### Conexões utilizadas nos experimentos

| Componente | Conexão no ESP32-C3 |
|---|---|
| Sensor de umidade — sinal analógico | GPIO 1 |
| Buzzer ativo — sinal | GPIO 4 |
| OLED — SDA (I²C) | GPIO 8 |
| OLED — SCL (I²C) | GPIO 9 |

**Atenção:** confira também VCC e GND de cada módulo, a pinagem real da placa e as tensões de alimentação antes de energizar o circuito.

## 💻 Executar o site localmente

O site é desenvolvido em **HTML, CSS e JavaScript** e não exige instalação de dependências web.

No terminal do Ubuntu:

```bash
cd ~/Dev/Oficinas/GlowUp-IoT-Oficina
python3 -m http.server 8004 --bind 127.0.0.1
```

Abra no navegador:

http://localhost:8004/

O progresso das atividades e a conferência dos materiais são armazenados no **`localStorage` do navegador**. Portanto, são locais a cada navegador/dispositivo; não há sincronização automática com uma conta.

## 📂 Estrutura básica

```text
GlowUp-IoT-Oficina/
├── index.html          # Página inicial e acesso às etapas
├── materiais.html      # Lista de materiais
├── etapa01.html        # Conhecendo o ESP32-C3
├── etapa02.html        # Experimentando o ESP32-C3
├── etapa03.html        # Sensor de umidade
├── etapa04.html        # Display OLED
├── etapa05.html        # Sistema integrado
├── etapa06.html        # Personalização com RoboEyes
├── style.css           # Estilos compartilhados
├── glowup_imagens/     # Imagens utilizadas nos roteiros (se presentes)
└── README.md
```

**Observação:** a organização de imagens, scripts e arquivos `.ino` pode variar conforme a versão local. Preserve os caminhos referenciados pelos arquivos HTML ao publicar.

## 📡 Publicação no GitHub Pages

1. Crie um repositório **público** chamado `GlowUp-IoT-Oficina`, sem inicializá-lo com outros arquivos.
2. Envie os arquivos do projeto para a branch `main`.
3. No GitHub, acesse **Settings → Pages**.
4. Em **Build and deployment**, selecione **Deploy from a branch**.
5. Escolha **`main`** e **`/ (root)`**; depois, clique em **Save**.

A oficina será acessível pelo endereço indicado no início deste README após a publicação.

## 👩‍💻 Créditos

**GlowUp IoT: Ciência Delas — Expressões da Natureza**  
**IFSP — Campus Hortolândia**  
**NuRIA — Núcleo de Robótica e Inteligência Artificial**

Projeto educacional voltado à aprendizagem prática e à participação de meninas e mulheres em ciência e tecnologia.
