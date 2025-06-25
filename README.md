# 🌫️ Detector de Fumaca - Monitor Inteligente de Gás com ESP8266

## 📌 Sobre o Projeto
Sistema de detecção de gás/fumaça com alertas inteligentes usando sensor MQ-2 e NodeMCU ESP8266, integrado ao app Blynk para monitoramento remoto.

**Funcionalidades principais:**
- Leitura suavizada dos níveis de gás
- Alertas graduais (aviso/perigo)
- Notificações push no smartphone
- Indicação visual (LED físico e virtual)

---

## 🛠️ Componentes
- NodeMCU ESP8266
- Sensor de gás MQ-2
- LED indicador (D4)
- Fonte de alimentação

---

## 📡 Como Funciona
1. O sensor MQ-2 detecta concentração de gases combustíveis.
2. O ESP8266 processa os dados com filtro de média móvel (5 leituras).
3. Os níveis são transmitidos via WiFi para o dashboard Blynk.
4. O sistema aciona alertas visuais e notificações conforme os limiares:
   - **Aviso (>300 ppm)**: Alerta prévio.
   - **Perigo (>1000 ppm)**: Aciona LED e notificação de emergência.

---

## 🖥️ Esquema de Ligação
| Sensor MQ-2 | NodeMCU |
|-------------|---------|
| VCC         | 3.3V    |
| GND         | GND     |
| AOUT        | A0      |
| LED (+)     | D4      |
| LED (-)     | GND     |

---

## ⚙️ Configuração Blynk
1. Criar novo template no app Blynk:
   - **Template ID**: `TMPL2ucB-5jH4`
   - **Template Name**: "Sensor de fumaça"
2. Adicionar widgets:
   - **Gauge (V0)**: Valor analógico
   - **LED (V1)**: Alarme de perigo
   - **LED (V2)**: Status do LED físico
   - **Notification (V3)**: Avisos

---

## 📋 Passo a Passo
1. Montar o circuito conforme esquema.
2. Carregar o código no NodeMCU (ajustar credenciais):
   ```cpp
   char ssid[] = "SEU_WIFI";
   char pass[] = "SENHA_WIFI";
3. Aguardar **20 segundos** para aquecimento do sensor.
4. Monitorar valores pelo **Serial Monitor** (configurado em 9600 baud).
5. Interagir com os widgets no app **Blynk**.

---

## ⚠️ Alertas
- **Notificação push automática** ao atingir nível perigoso (>1000 ppm).
- Evento registrado no **log do Blynk** com valor exato da concentração.

---

## 📊 Pinos Virtuais Blynk
| Pino | Função                   |
|------|--------------------------|
| V0   | Valor médio do sensor    |
| V1   | Alarme sonoro virtual    |
| V2   | Controle do LED físico   |
| V3   | Notificação de aviso     |

---

## 🔧 Troubleshooting (Soluções Comuns)
| Problema               | Ação Recomendada                          |
|------------------------|------------------------------------------|
| Falha na conexão       | Verificar credenciais WiFi e token Blynk |
| Leituras instáveis     | Aguardar aquecimento completo do sensor |
| LED não aciona         | Verificar ligação física e pino definido |

---

## 👥 Créditos
**Desenvolvido por:** Davi Rosa Gomes
**Disciplina:** Conceitos e Tecnologias para Dispositivos Conectados  
**Professor:** Samuel Baraldi Mafra  
