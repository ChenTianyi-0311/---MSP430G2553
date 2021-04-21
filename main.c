#include <msp430.h> 

void main( void )
{
    WDTCTL = WDTPW | WDTHOLD;   // arret du Watchdog
    P1DIR |= BIT6;
    P1DIR &= ~(BIT3);
    P1REN |= BIT3;              // activation resistance interne
    P1OUT |= BIT3;              // mode pull-up
    P1IE |= BIT3;               // activation interruption
    P1IES |= BIT3;              // interruption sur front descendant
                                // donc appui car bouton connecte a la masse
    P1IFG &= ~(BIT3);           // RAZ flag d’interruption
    __enable_interrupt();         // autorisation generale des interruptions
    while(1)
    {
        __delay_cycles(500000);       //delai pour simuler un traitement
    }
}

#pragma vector=PORT1_VECTOR
__interrupt void detect_bouton(void)
{
    P1OUT ^= (BIT6) ;
    __delay_cycles(1000000);
    P1IFG &= ~(BIT3);
}
