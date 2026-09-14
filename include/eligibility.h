#ifndef ELIGIBILITY_H
#define ELIGIBILITY_H

#include "student.h"
#include "drive.h"

/*
 * Checks whether a student is eligible
 * for a placement drive.
 *
 * Returns:
 * 1 -> Eligible
 * 0 -> Not Eligible
 */
int checkStudentEligibility(const Student *student,
                            const PlacementDrive *drive);

/* Interactive eligibility checker */
void eligibilityChecker(void);

#endif