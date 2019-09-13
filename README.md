# Esperimenti di Domain Driven Design in C++

Il repository contiene il materiale di supporto per la presentazione riguardante un esperimento di Domain Driven Design svolta al Meetup C++ di Modena del 12 Settembre 2019:

* slide;
* file di esempio in c++.

## Problema

Veniamo incaricati di progettare un programma di supporto alla organizzazione dei Meetup C++ di Modena, in modo da automatizzare alcune operazioni e interagire con sistemi gi&agrave; esistenti.

In particolare supponiamo esista gi&agrave; un sistema di raccolta proposte fatto con un form web (es. Google Moduli) diviso in due parti:

* nella prima parte un relatore registra le proprie informazioni (nome, indirizzo email, identificativo twitter, ecc.)
* nella seconda parte il relatore pu&ograve; inserire una o pi&ugrave; proposte di presentazione e le date in cui è disponibile a effettuarle.

Quando arriva il momento in cui creare il calendario dei Meetup, viene scaricato il file dei form (es. formato json) e dato come input al nostro programma che dovr&agrave;:

* validare i dati di ingresso;
* invocare un programma esterno per assegnare un voto a ciascuna presentazione (es. richiesta interattiva all'utente, valutazione automatica tramite Intelligenza Artificiale);
* elaborare il calendario delle presentazioni, assegnando in preferenza quelle con il voto pi&ugrave; alto.


