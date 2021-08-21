# Minecraft Clone com C++ e SFML

### Criar um diretório de desenvolvimento

- Exemplo:

```cmd
	mkdir Game-Projects
```

### Baixar SFML

https://www.sfml-dev.org/

- Descompatar os arquivos dentro do diretório de desenvolvimento.

- Renomear a pasta do SFML apenas para `SFML`.


### Criar uma solução do Visual Studio

- Criar a solução no diretório de desenvolvimento onde está a biblioteca do SFML.

- Criar um projeto C++ vazio.

### Configurações do Projeto

- Copiar todos os arquivos em `SFML\bin` para a raiz do diretório do projeto.

- Clicar em __Projeto__.

- Selecionar a opção `Propriedades de <Nome do Projeto>`.

- Em `Configuração` selecionar `Todas as Configurações`.

- Selecionar a opção `C++`.

- Selecionar a opção `Diretórios de inclusão Adicionais`.

- Clicar em __Editar__.

- Digitar a linha: `$(SolutionDir)..\SFML\include`.

- Clicar em __OK__.

- Selecionar a opção `Vinculador`.

- Selecionar a opção `Diretórios de biblioteca Adicionais`.

- Clicar em __Editar__.

- Digitar a linha: `$(SolutionDir)..\SFML\lib`.

- Clicar em __OK__.

- Clicar em __Aplicar__.

- Em `Configuração` alterar para `Release`.

- Selecionar `Vinculador`.

- Selecionar `Entrada`.

- Selecionar `Dependências Adicionais`.

- Clicar em __Editar__.

- Digitar as linhas abaixo:

```cmd
sfml-graphics.lib
sfml-network.lib
sfml-system.lib
sfml-window.lib
sfml-audio.lib
"opengl32.lib"
"glu32.lib"
```

- Clicar em __OK__.

- Clicar em __Aplicar__.

- Em `Configuração` selecionar `Debug`.

- Selecionar `Vinculador`.

- Selecionar `Entrada`.

- Selecionar `Dependências Adicionais`.

- Clicar em __Editar__.

- Digitar as linhas abaixo:

```cmd
sfml-graphics-d.lib
sfml-network-d.lib
sfml-system-d.lib
sfml-window-d.lib
sfml-audio-d.lib
"opengl32.lib"
"glu32.lib"
```

- Clicar em __OK__.

- Clicar em __Aplicar__.


### Testando com SFML

Ref: https://www.sfml-dev.org/tutorials/2.5/start-vc.php

- Crie um arquivo `main.cpp` em `Arquivos de Origem` e adicione o código a seguir:

```c++
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
```

### Gerando um Executável

- É necessário copiar todas as `dll's` dentro de `SFML/bin` para o diretório `Debug` e `Release`
- É necessário copiar o diretório de `resources` para o diretório `Debug` e `Release`

#### Criando um icone para o executável.
  
- Precisa ser um arquivo com a extensão `.ico`.
- Abrir o `Modo de Exibição de Recursos` do Visual Studio.
- Clicar com o botão direito no nome do projeto em `Modo de Exibição de Recursos`.
- Selecionar a opção __Adicionar__.
- Selecionar a opção __Recurso__.
- Selecionar a opção __Icon__.
- Clicar em __Importar__.
- Selecionar o arquivo com a extensão `.ico`.
- Clicar em __Depurar__.
- Clicar em __Iniciar Depuração__ para gerar o executável com o icone escolhido.

### Gerando Executável com Link Estático

- Clicar em __Projeto__
- Selecionar __Propriedades de __<Nome do Projeto>.__
- Escolher a opção `Release` ou `Debug` em configuração.
- Selecionar a opção `C++`.
- Selecionar a opção `Pré-processador`.
- Clicar em `Definições do Pré-processador`.
- Clicar em __Editar__.
- Adicionar a linha `SFML_STATIC`.
- Clicar em __OK__.
- Clicar em __Aplicar__.
- Clicar em __Vinculador__.
- Selecionar `Entrada`.
- Clicar em `Dependências Adicionais`.
- Remover todas as dependências atuais e colocar as dependências abaixo:

```cmd
sfml-graphics-s.lib
sfml-window-s.lib
sfml-system-s.lib
opengl32.lib
freetype.lib	
winmm.lib
gdi32.lib
sfml-audio-s.lib
openal32.lib
flac.lib
vorbisenc.lib
vorbisfile.lib
vorbis.lib
ogg.lib
sfml-network-s.lib
ws2_32.lib	
winmm.lib
"opengl32.lib"
"glu32.lib"
```

- Clicar em __OK__.
- Clicar em __Aplicar__.
- Clicar em __OK__.
- Clicar em Iniciar Depuração.

#### Testando Executável

- Criar uma pasta `Minecraft`.
- Copiar o Executável para dentro da pasta `Minecraft`.
- Copiar a pasta `resources` para dentro da pasta `Minecraft`.
- Copiar o arquivo `openal32.dll` para dentro da pasta `Minecraft`.
- Executar!