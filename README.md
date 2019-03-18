# Polynomial-reduction-from-the-Hamiltonian-Cycle-problem-to-SAT-problem

Pislari Vadim -> Facultatea Automatica si Calculatoare -> Universitatea Politehnica Bucuresti

                                                 (Romanian language)
                                               -------DESCRIERE-------
      Un drum hamiltonian intr-un graf neorientat, este un drum care viziteaza fiecare nod o singura data.
Un ciclu hamiltonian este un drum hamiltonian care reprezinta, totodata, un ciclu.
Problema Hamiltonian Cycle consta in determinarea daca un astfel de ciclu exista sau nu intr-un graf.
Un ciclu intr-un graf G = (V, E) reprezinta o succesiune de noduri v1, v2, v3, ..., vn, vi ∈ V, ∀i ∈
{1, 2, ..., n}, cu proprietatea ca v1 = vn si (vi, vi+1) ∈ E, ∀i ∈ {1, 2, ..., n − 1}.

Proiectul isi propune realizarea unei transformari T, polinomiala, prin care se reduce Hamiltonian Cycle 
Problem la SAT. HCP ≤P SAT
Astfel, transformarea T va primi ca input o instanta a problemei Hamiltonian Cycle (un graf) si va
trebui sa intoarca o instanta a problemei SAT (o expresie booleana).


Valoarea variabilei N este restrictionata: 1 ≤ N ≤ 100

xi−j =  1, daca muchia (i, j) apartine drumului ales 
        0, altfel  1 ≤ i, j ≤ N
ai−j =  1, daca cea mai scurta cale de la 1 la j, in drumul ales, are lungimea i
        0, altfel 1 ≤ i ≤ N/2+1, 1 ≤ j ≤ N
