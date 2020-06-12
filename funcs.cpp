#include <iostream>
#include <math.h>

#include "TGraph.h"
#include "TCanvas.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TH2F.h"

using namespace std;

#define MAX 14

/*class Core{
	private:*/

double n[MAX], nfact[MAX], nfqrt[MAX], expon[MAX], nlogn[MAX];
	/*public:*/

int factorial(int num){
	unsigned long long int fact = 1;
	for (int i = fact; i <= num; i++){
		fact *= i;
	}
	// cout <<"fact: "<< fact <<endl;
	return fact;
}

/*};*/


void funcs(){
	TCanvas *c = new TCanvas("Series Functions", "Growing Series Functions", 200, 10, 1400, 720);
	c->SetGrid();
	c->SetFillColor(42);
	// c->GetFrame()->SetFillColor(21);
	// c->GetFrame()->SetBorderSize(21);
	
	TH2F *hpx = new TH2F("hpx","Zoomed Graph Example",10,0,0.5,10,1.0,8.0);
	hpx->SetStats(kTRUE);// no statistics
	hpx->Draw();
	
	// Tgraph
	for (int i = 1; i < MAX; i++){

		n[i] = i;

		/* With Logarithmic Scale *//**/
		nlogn[i] = 120 * log10( pow(i, log10(i) ) );
		expon[i] = 120 * log10( exp(i) );
		nfqrt[i] = 120 * log10( sqrt( factorial(i) ) );
		nfact[i] = 120 * log10( factorial(i) );
		/**/

		/* Without Logarithmic Scale *//**
		n[i] = i;
		nlogn[i] = pow(i, log10(i) );
		expon[i] = exp(i);
		nfqrt[i] = sqrt( factorial(i) );
		nfact[i] = factorial(i);
		**/
	}
	
	for (int i = 0; i < MAX; i++){
		cout <<"n: "<< n[i] <<"\tnfact: "<< nfact[i] <<"\tnlogn: "<<nlogn[i]<<"\texpon: "<<expon[i]<<"\tnfqrt: "<<nfqrt[i]<<endl;
	}

	// creating the graph
	TGraph *g_nlogn = new TGraph(MAX, n, nlogn);
	TGraph *g_expon = new TGraph(MAX, n, expon);
	TGraph *g_nfqrt = new TGraph(MAX, n, nfqrt);
	TGraph *g_nfact = new TGraph(MAX, n, nfact);

	// line-plot
	g_nlogn->SetLineColor(kRed);
	g_nlogn->SetLineWidth(4);
	g_expon->SetLineColor(kGreen);
	g_expon->SetLineWidth(4);
	g_nfqrt->SetLineColor(kCyan);
	g_nfqrt->SetLineWidth(4);
	g_nfact->SetLineColor(kBlue);
	g_nfact->SetLineWidth(4);

	// Create MultiGraph
	TMultiGraph *mg = new TMultiGraph("Multigraph", "Growing Series Functions");
	mg->SetTitle("n - Series Growth Functions (logarithmic scale) ");
	mg->GetXaxis()->SetTitle("X-axis = n values");
        mg->GetYaxis()->SetTitle("Y-axis = magnitude");

	mg->Add(g_nlogn);
	mg->Add(g_expon);
	mg->Add(g_nfqrt);
	mg->Add(g_nfact);
	mg->Draw("ACP");

	// TLegend
	TLegend legd(0.1, 0.5, 0.36, 0.9, "n - Series Growth Functions");
	legd.SetFillColor(21);
	legd.AddEntry(g_nfact, " n! ");
	legd.AddEntry(g_expon, " e^(n) ");
	legd.AddEntry(g_nfqrt, " sqrt(n!) ");
	legd.AddEntry(g_nlogn, " n^(log n) ");
	legd.DrawClone("Same");
}


int main(int argc, char *argv[]){

	/*Core growth;
	growth.funcs();*/
	funcs();
	return 0;
}
