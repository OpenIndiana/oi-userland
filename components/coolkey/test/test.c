/*
 * This file is to be used for in-house testing purposes only, it has been 
 * modified from the test program source of the CACKey v0.7.4 component 
 * and adapted for use with this Solaris coolkey v1.1.0 userland component.
 */

#include "mypkcs11.h"
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


static char *pkcs11_attribute_to_name(CK_ATTRIBUTE_TYPE attrib) {
	static char retbuf[1024];

	switch (attrib) {
		case 0x00000000: return "CKA_CLASS";
		case 0x00000001: return "CKA_TOKEN";
		case 0x00000002: return "CKA_PRIVATE";
		case 0x00000003: return "CKA_LABEL";
		case 0x00000010: return "CKA_APPLICATION";
		case 0x00000011: return "CKA_VALUE";
		case 0x00000012: return "CKA_OBJECT_ID";
		case 0x00000080: return "CKA_CERTIFICATE_TYPE";
		case 0x00000081: return "CKA_ISSUER";
		case 0x00000082: return "CKA_SERIAL_NUMBER";
		case 0x00000083: return "CKA_AC_ISSUER";
		case 0x00000084: return "CKA_OWNER";
		case 0x00000085: return "CKA_ATTR_TYPES";
		case 0x00000086: return "CKA_TRUSTED";
		case 0x00000100: return "CKA_KEY_TYPE";
		case 0x00000101: return "CKA_SUBJECT";
		case 0x00000102: return "CKA_ID";
		case 0x00000103: return "CKA_SENSITIVE";
		case 0x00000104: return "CKA_ENCRYPT";
		case 0x00000105: return "CKA_DECRYPT";
		case 0x00000106: return "CKA_WRAP";
		case 0x00000107: return "CKA_UNWRAP";
		case 0x00000108: return "CKA_SIGN";
		case 0x00000109: return "CKA_SIGN_RECOVER";
		case 0x0000010A: return "CKA_VERIFY";
		case 0x0000010B: return "CKA_VERIFY_RECOVER";
		case 0x0000010C: return "CKA_DERIVE";
		case 0x00000110: return "CKA_START_DATE";
		case 0x00000111: return "CKA_END_DATE";
		case 0x00000120: return "CKA_MODULUS";
		case 0x00000121: return "CKA_MODULUS_BITS";
		case 0x00000122: return "CKA_PUBLIC_EXPONENT";
		case 0x00000123: return "CKA_PRIVATE_EXPONENT";
		case 0x00000124: return "CKA_PRIME_1";
		case 0x00000125: return "CKA_PRIME_2";
		case 0x00000126: return "CKA_EXPONENT_1";
		case 0x00000127: return "CKA_EXPONENT_2";
		case 0x00000128: return "CKA_COEFFICIENT";
		case 0x00000130: return "CKA_PRIME";
		case 0x00000131: return "CKA_SUBPRIME";
		case 0x00000132: return "CKA_BASE";
		case 0x00000133: return "CKA_PRIME_BITS";
		case 0x00000134: return "CKA_SUB_PRIME_BITS";
		case 0x00000160: return "CKA_VALUE_BITS";
		case 0x00000161: return "CKA_VALUE_LEN";
		case 0x00000162: return "CKA_EXTRACTABLE";
		case 0x00000163: return "CKA_LOCAL";
		case 0x00000164: return "CKA_NEVER_EXTRACTABLE";
		case 0x00000165: return "CKA_ALWAYS_SENSITIVE";
		case 0x00000166: return "CKA_KEY_GEN_MECHANISM";
		case 0x00000170: return "CKA_MODIFIABLE";
		case 0x00000180: return "CKA_EC_PARAMS";
		case 0x00000181: return "CKA_EC_POINT";
		case 0x00000200: return "CKA_SECONDARY_AUTH";
		case 0x00000201: return "CKA_AUTH_PIN_FLAGS";
		case 0x00000300: return "CKA_HW_FEATURE_TYPE";
		case 0x00000301: return "CKA_RESET_ON_INIT";
		case 0x00000302: return "CKA_HAS_RESET";
		case 0xce5363b4: return "CKA_CERT_SHA1_HASH";
		case 0xce5363b5: return "CKA_CERT_MD5_HASH";
	}

	snprintf(retbuf, sizeof(retbuf), "0x%08lx", (unsigned long) attrib);
	retbuf[sizeof(retbuf) - 1] = '\0';

	return(retbuf);
}

int main_pkcs11(void) {
	CK_FUNCTION_LIST_PTR pFunctionList;
	CK_RV (*C_CloseSession)(CK_SESSION_HANDLE hSession) = NULL;
	CK_RV (*C_Decrypt)(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pEncryptedData, CK_ULONG ulEncryptedDataLen, CK_BYTE_PTR pData, CK_ULONG_PTR pulDataLen) = NULL;
	CK_RV (*C_DecryptInit)(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey) = NULL;
	CK_RV (*C_Encrypt)(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pEncryptedData, CK_ULONG_PTR pulEncryptedDataLen) = NULL;
	CK_RV (*C_EncryptInit)(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey) = NULL;
	CK_RV (*C_Finalize)(CK_VOID_PTR pReserved) = NULL;
	CK_RV (*C_FindObjects)(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE_PTR phObject, CK_ULONG ulMaxObjectCount, CK_ULONG_PTR pulObjectCount) = NULL;
	CK_RV (*C_FindObjectsFinal)(CK_SESSION_HANDLE hSession) = NULL;
	CK_RV (*C_FindObjectsInit)(CK_SESSION_HANDLE hSession, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount) = NULL;
	CK_RV (*C_GetAttributeValue)(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount) = NULL;
	CK_RV (*C_GetInfo)(CK_INFO_PTR pInfo) = NULL;
	CK_RV (*C_GetSessionInfo)(CK_SESSION_HANDLE hSession, CK_SESSION_INFO_PTR pInfo) = NULL;
	CK_RV (*C_GetSlotInfo)(CK_SLOT_ID slotID, CK_SLOT_INFO_PTR pInfo) = NULL;
	CK_RV (*C_GetSlotList)(CK_BBOOL tokenPresent, CK_SLOT_ID_PTR pSlotList, CK_ULONG_PTR pulCount) = NULL;
	CK_RV (*C_GetTokenInfo)(CK_SLOT_ID slotID, CK_TOKEN_INFO_PTR pInfo) = NULL;
	CK_RV (*C_Initialize)(CK_VOID_PTR pInitArgs) = NULL;
	CK_RV (*C_Login)(CK_SESSION_HANDLE hSession, CK_USER_TYPE userType, CK_UTF8CHAR_PTR pPin, CK_ULONG ulPinLen) = NULL;
	CK_RV (*C_OpenSession)(CK_SLOT_ID slotID, CK_FLAGS flags, CK_VOID_PTR pApplication, CK_NOTIFY notify, CK_SESSION_HANDLE_PTR phSession) = NULL;
	CK_RV (*C_Sign)(CK_SESSION_HANDLE hSession, CK_BYTE_PTR pData, CK_ULONG ulDataLen, CK_BYTE_PTR pSignature, CK_ULONG_PTR pulSignatureLen) = NULL;
	CK_RV (*C_SignInit)(CK_SESSION_HANDLE hSession, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey) = NULL;
	CK_C_INITIALIZE_ARGS initargs;
	CK_INFO clientinfo;
	CK_ULONG numSlots, currSlot;
	CK_SLOT_ID_PTR slots;
	CK_SLOT_INFO slotInfo;
	CK_TOKEN_INFO tokenInfo;
	CK_SESSION_HANDLE hSession;
	CK_SESSION_INFO sessionInfo;
	CK_OBJECT_HANDLE hObject, *privateKeyObjects_root, *privateKeyObjects, *currPrivKey;
	CK_ULONG ulObjectCount;
	CK_ATTRIBUTE template[] = {
	                           {CKA_CLASS, NULL, 0},
	                           {CKA_TOKEN, NULL, 0},
	                           {CKA_LABEL, NULL, 0},
	                           {CKA_PRIVATE, NULL, 0},
	                           {CKA_ID, NULL, 0},
	                           {CKA_SERIAL_NUMBER, NULL, 0},
	                           {CKA_SUBJECT, NULL, 0},
	                           {CKA_ISSUER, NULL, 0},
	                           {CKA_CERTIFICATE_TYPE, NULL, 0},
	                           {CKA_KEY_TYPE, NULL, 0},
	                           {CKA_SIGN, NULL, 0},
	                           {CKA_VALUE, NULL, 0},
				   {CKA_TRUSTED, NULL, 0}
	                          }, *curr_attr;
	CK_ULONG curr_attr_idx;
	CK_ULONG byte_idx;
	CK_UTF8CHAR user_pin[1024], *pucValue;
	CK_OBJECT_CLASS objectClass;
	CK_BYTE signature[1024], encrypted_buf[16384], decrypted_buf[16384];
	CK_ULONG signature_len, encrypted_buflen, decrypted_buflen;
	CK_MECHANISM mechanism = {CKM_RSA_PKCS, NULL, 0};
	CK_RV chk_rv;
	char *fgets_ret;
	int i;

	chk_rv = C_GetFunctionList(&pFunctionList);
	if (chk_rv != CKR_OK) {
		printf("C_GetFunctionList() failed.");

		return(1);
	}

	C_CloseSession = pFunctionList->C_CloseSession;
	C_Decrypt = pFunctionList->C_Decrypt;
	C_DecryptInit = pFunctionList->C_DecryptInit;
	C_Encrypt = pFunctionList->C_Encrypt;
	C_EncryptInit = pFunctionList->C_EncryptInit;
	C_Finalize = pFunctionList->C_Finalize;
	C_FindObjects = pFunctionList->C_FindObjects;
	C_FindObjectsFinal = pFunctionList->C_FindObjectsFinal;
	C_FindObjectsInit = pFunctionList->C_FindObjectsInit;
	C_GetAttributeValue = pFunctionList->C_GetAttributeValue;
	C_GetInfo = pFunctionList->C_GetInfo;
	C_GetSessionInfo = pFunctionList->C_GetSessionInfo;
	C_GetSlotInfo = pFunctionList->C_GetSlotInfo;
	C_GetSlotList = pFunctionList->C_GetSlotList;
	C_GetTokenInfo = pFunctionList->C_GetTokenInfo;
	C_Initialize = pFunctionList->C_Initialize;
	C_Login = pFunctionList->C_Login;
	C_OpenSession = pFunctionList->C_OpenSession;
	C_Sign = pFunctionList->C_Sign;
	C_SignInit = pFunctionList->C_SignInit;

	privateKeyObjects = malloc(sizeof(*privateKeyObjects) * 1024);
	privateKeyObjects_root = privateKeyObjects;
	for (i = 0; i < 1024; i++) {
		privateKeyObjects[i] = CK_INVALID_HANDLE;
	}

	initargs.CreateMutex = NULL;
	initargs.DestroyMutex = NULL;
	initargs.LockMutex = NULL;
	initargs.UnlockMutex = NULL;
	initargs.flags = CKF_OS_LOCKING_OK;
	initargs.LibraryParameters = NULL;
	initargs.pReserved = NULL;

	chk_rv = C_Initialize(&initargs);
	if (chk_rv != CKR_OK) {
		initargs.CreateMutex = NULL;
		initargs.DestroyMutex = NULL;
		initargs.LockMutex = NULL;
		initargs.UnlockMutex = NULL;
		initargs.flags = 0;
		initargs.LibraryParameters = NULL;	
		initargs.pReserved = NULL;

		chk_rv = C_Initialize(&initargs);
		if (chk_rv != CKR_OK) {
			printf("C_Initialize() failed.");

			return(1);
		}
	}

	chk_rv = C_GetInfo(&clientinfo);
	if (chk_rv != CKR_OK) {
		return(1);
	}

	printf("PKCS#11 Client Version: %i.%i, Library Version %i.%i\n", clientinfo.cryptokiVersion.major, clientinfo.cryptokiVersion.minor, clientinfo.libraryVersion.major, clientinfo.libraryVersion.minor);
	printf("PKCS#11 ManufID: %.*s, LibraryDesc: %.*s\n", 32, clientinfo.manufacturerID, 32, clientinfo.libraryDescription);

	chk_rv = C_GetSlotList(FALSE, NULL, &numSlots);
	if (chk_rv != CKR_OK) {
		return(1);
	}

	printf("Number of Slots: %lu\n", numSlots);

	slots = malloc(sizeof(*slots) * numSlots);

	chk_rv = C_GetSlotList(FALSE, slots, &numSlots);
	if (chk_rv != CKR_OK) {
		return(1);
	}

	for (currSlot = 0; currSlot < numSlots; currSlot++) {
		printf("  Slot %lu:\n", currSlot);

		chk_rv = C_GetSlotInfo(slots[currSlot], &slotInfo);
		if (chk_rv != CKR_OK) {
			return(1);
		}

		printf("    Id     : %lu\n", (unsigned long) slots[currSlot]);
		printf("    Desc   : %.*s\n", 32, slotInfo.slotDescription);
		printf("    ManufID: %.*s\n", 32, slotInfo.manufacturerID);
		printf("    HWVers : %i.%i\n", slotInfo.hardwareVersion.major, slotInfo.hardwareVersion.minor);
		printf("    FWVers : %i.%i\n", slotInfo.firmwareVersion.major, slotInfo.firmwareVersion.minor);
		printf("    Flags  : ");
		if ((slotInfo.flags & CKF_TOKEN_PRESENT) == CKF_TOKEN_PRESENT) {
			printf("CKF_TOKEN_PRESENT ");
		}
		if ((slotInfo.flags & CKF_REMOVABLE_DEVICE) == CKF_REMOVABLE_DEVICE) {
			printf("CKF_REMOVABLE_DEVICE ");
		}
		if ((slotInfo.flags & CKF_HW_SLOT) == CKF_HW_SLOT) {
			printf("CKF_HW_SLOT ");
		}
		printf("\n");

		if ((slotInfo.flags & CKF_TOKEN_PRESENT) == CKF_TOKEN_PRESENT) {
			printf("    Token:\n");

			chk_rv = C_GetTokenInfo(slots[currSlot], &tokenInfo);
			if (chk_rv != CKR_OK) {
				return(1);
			}

			printf("      Label  : %.*s\n", 32, tokenInfo.label);
			printf("      ManufID: %.*s\n", 32, tokenInfo.manufacturerID);
			printf("      Model  : %.*s\n", 16, tokenInfo.model);
			printf("      SerNo  : %.*s\n", 16, tokenInfo.serialNumber);
			printf("      HWVers : %i.%i\n", tokenInfo.hardwareVersion.major, tokenInfo.hardwareVersion.minor);
			printf("      FWVers : %i.%i\n", tokenInfo.firmwareVersion.major, tokenInfo.firmwareVersion.minor);
			printf("      Flags  : ");
			if ((tokenInfo.flags & CKF_RNG) == CKF_RNG) {
				printf("CKF_RNG ");
			}
			if ((tokenInfo.flags & CKF_WRITE_PROTECTED) == CKF_WRITE_PROTECTED) {
				printf("CKF_WRITE_PROTECTED ");
			}
			if ((tokenInfo.flags & CKF_LOGIN_REQUIRED) == CKF_LOGIN_REQUIRED) {
				printf("CKF_LOGIN_REQUIRED ");
			}
			if ((tokenInfo.flags & CKF_USER_PIN_INITIALIZED) == CKF_USER_PIN_INITIALIZED) {
				printf("CKF_USER_PIN_INITIALIZED ");
			}
			if ((tokenInfo.flags & CKF_RESTORE_KEY_NOT_NEEDED) == CKF_RESTORE_KEY_NOT_NEEDED) {
				printf("CKF_RESTORE_KEY_NOT_NEEDED ");
			}
			if ((tokenInfo.flags & CKF_CLOCK_ON_TOKEN) == CKF_CLOCK_ON_TOKEN) {
				printf("CKF_CLOCK_ON_TOKEN ");
			}
			if ((tokenInfo.flags & CKF_PROTECTED_AUTHENTICATION_PATH) == CKF_PROTECTED_AUTHENTICATION_PATH) {
				printf("CKF_PROTECTED_AUTHENTICATION_PATH ");
			}
			if ((tokenInfo.flags & CKF_DUAL_CRYPTO_OPERATIONS) == CKF_DUAL_CRYPTO_OPERATIONS) {
				printf("CKF_DUAL_CRYPTO_OPERATIONS ");
			}
			if ((tokenInfo.flags & CKF_TOKEN_INITIALIZED) == CKF_TOKEN_INITIALIZED) {
				printf("CKF_TOKEN_INITIALIZED ");
			}
			if ((tokenInfo.flags & CKF_SECONDARY_AUTHENTICATION) == CKF_SECONDARY_AUTHENTICATION) {
				printf("CKF_SECONDARY_AUTHENTICATION ");
			}
			if ((tokenInfo.flags & CKF_USER_PIN_COUNT_LOW) == CKF_USER_PIN_COUNT_LOW) {
				printf("CKF_USER_PIN_COUNT_LOW ");
			}
			if ((tokenInfo.flags & CKF_USER_PIN_FINAL_TRY) == CKF_USER_PIN_FINAL_TRY) {
				printf("CKF_USER_PIN_FINAL_TRY ");
			}
			if ((tokenInfo.flags & CKF_USER_PIN_LOCKED) == CKF_USER_PIN_LOCKED) {
				printf("CKF_USER_PIN_LOCKED ");
			}
			if ((tokenInfo.flags & CKF_USER_PIN_TO_BE_CHANGED) == CKF_USER_PIN_TO_BE_CHANGED) {
				printf("CKF_USER_PIN_TO_BE_CHANGED ");
			}
			if ((tokenInfo.flags & CKF_SO_PIN_COUNT_LOW) == CKF_SO_PIN_COUNT_LOW) {
				printf("CKF_SO_PIN_COUNT_LOW ");
			}
			if ((tokenInfo.flags & CKF_SO_PIN_FINAL_TRY) == CKF_SO_PIN_FINAL_TRY) {
				printf("CKF_SO_PIN_FINAL_TRY ");
			}
			if ((tokenInfo.flags & CKF_SO_PIN_LOCKED) == CKF_SO_PIN_LOCKED) {
				printf("CKF_SO_PIN_LOCKED ");
			}
			if ((tokenInfo.flags & CKF_SO_PIN_TO_BE_CHANGED) == CKF_SO_PIN_TO_BE_CHANGED) {
				printf("CKF_SO_PIN_TO_BE_CHANGED ");
			}
			printf("\n");
		}
	}

	chk_rv = C_OpenSession(slots[0], CKF_SERIAL_SESSION, NULL, NULL, &hSession);
	if (chk_rv == CKR_OK) {
		chk_rv = C_GetTokenInfo(slots[0], &tokenInfo);
		if (chk_rv != CKR_OK) {
			return(1);
		}

		if ((tokenInfo.flags & CKF_LOGIN_REQUIRED) == CKF_LOGIN_REQUIRED && (tokenInfo.flags & CKF_PROTECTED_AUTHENTICATION_PATH) == 0) {
			fgets_ret = NULL;

			while (fgets_ret == NULL) {
				printf("** ENTER PIN: ");
				fflush(stdout);

				fgets_ret = fgets((char *) user_pin, sizeof(user_pin), stdin);
			}

			if (strlen((char *) user_pin) >= 1) {
				while (user_pin[strlen((char *) user_pin) - 1] < ' ') {
					user_pin[strlen((char *) user_pin) - 1] = '\0';
				}
			}

			chk_rv = C_Login(hSession, CKU_USER, user_pin, strlen((char *) user_pin));
		} else {
			chk_rv = C_Login(hSession, CKU_USER, NULL, 0);
		}
		if (chk_rv == CKR_OK) {
			printf("Login to device succeed.\n");
		} else {
			printf("Login to device failed.\n");
		}

		chk_rv = C_GetSessionInfo(hSession, &sessionInfo);
		if (chk_rv == CKR_OK) {
			printf("Session Info:\n");
			printf("  Slot ID: %lu\n", (unsigned long) sessionInfo.slotID);
			printf("  Dev Err: %lu\n", (unsigned long) sessionInfo.ulDeviceError);

			printf("  State  : ");
			if (sessionInfo.state == CKS_RO_PUBLIC_SESSION) {
				printf("CKS_RO_PUBLIC_SESSION\n");
			} else if (sessionInfo.state == CKS_RO_USER_FUNCTIONS) {
				printf("CKS_RO_USER_FUNCTIONS\n");
			} else if (sessionInfo.state == CKS_RW_PUBLIC_SESSION) {
				printf("CKS_RW_PUBLIC_SESSION\n");
			} else if (sessionInfo.state == CKS_RW_USER_FUNCTIONS) {
				printf("CKS_RW_USER_FUNCTIONS\n");
			} else if (sessionInfo.state == CKS_RO_PUBLIC_SESSION) {
				printf("CKS_RW_SO_FUNCTIONS\n");
			} else {
				printf("Unknown (%lu)", (unsigned long) sessionInfo.state);
			}

			printf("  Flags  : ");
			if ((sessionInfo.flags & CKF_RW_SESSION) == CKF_RW_SESSION) {
				printf("CKF_RW_SESSION ");
			}
			if ((sessionInfo.flags & CKF_SERIAL_SESSION) == CKF_SERIAL_SESSION) {
				printf("CKF_SERIAL_SESSION ");
			}
			printf("\n");
		} else {
			printf("GetSessionInfo() failed.\n");
		}

		chk_rv = C_FindObjectsInit(hSession, NULL, 0);
		if (chk_rv == CKR_OK) {
			while (1) {
				chk_rv = C_FindObjects(hSession, &hObject, 1, &ulObjectCount);
				if (chk_rv != CKR_OK) {
					printf("FindObjects() failed.\n");
					break;
				}

				if (ulObjectCount == 0) {
					break;
				}

				if (ulObjectCount != 1) {
					printf("FindObjects() returned a weird number of objects.  Asked for 1, got %lu.\n", ulObjectCount);
					break;
				}

				printf("  Object Info (object %lu):\n", (unsigned long) hObject);

				for (curr_attr_idx = 0; curr_attr_idx < (sizeof(template) / sizeof(template[0])); curr_attr_idx++) {
					curr_attr = &template[curr_attr_idx];
					if (curr_attr->pValue) {
						free(curr_attr->pValue);
					}

					curr_attr->pValue = NULL;
				}

				chk_rv = C_GetAttributeValue(hSession, hObject, &template[0], sizeof(template) / sizeof(template[0]));
				if (chk_rv == CKR_ATTRIBUTE_TYPE_INVALID || chk_rv == CKR_ATTRIBUTE_SENSITIVE || chk_rv == CKR_BUFFER_TOO_SMALL) {
					chk_rv = CKR_OK;
				}

				if (chk_rv == CKR_OK) {
					for (curr_attr_idx = 0; curr_attr_idx < (sizeof(template) / sizeof(template[0])); curr_attr_idx++) {
						curr_attr = &template[curr_attr_idx];

						if (((CK_LONG) curr_attr->ulValueLen) != ((CK_LONG) -1)) {
							curr_attr->pValue = malloc(curr_attr->ulValueLen);
						}
					}

					chk_rv = C_GetAttributeValue(hSession, hObject, &template[0], sizeof(template) / sizeof(template[0]));
					if (chk_rv == CKR_OK || chk_rv == CKR_ATTRIBUTE_SENSITIVE || chk_rv == CKR_ATTRIBUTE_TYPE_INVALID || chk_rv == CKR_BUFFER_TOO_SMALL) {
						for (curr_attr_idx = 0; curr_attr_idx < (sizeof(template) / sizeof(template[0])); curr_attr_idx++) {
							curr_attr = &template[curr_attr_idx];

							if (curr_attr->pValue) {
								switch (curr_attr->type) {
									case CKA_LABEL:
										printf("    [%lu] %20s: %.*s\n", hObject, pkcs11_attribute_to_name(curr_attr->type), (int) curr_attr->ulValueLen, (char *) curr_attr->pValue);
										break;
									case CKA_CLASS:
										objectClass = *((CK_OBJECT_CLASS *) curr_attr->pValue);

										if (objectClass == CKO_PRIVATE_KEY) {
											*privateKeyObjects = hObject;
											privateKeyObjects++;
										}
									case CKA_TOKEN:
									case CKA_ID:
									case CKA_SERIAL_NUMBER:
									case CKA_PRIVATE:
									case CKA_CERTIFICATE_TYPE:
									case CKA_KEY_TYPE:
									case CKA_SIGN:
									case CKA_DECRYPT:
									case CKA_TRUSTED:
									
										pucValue = curr_attr->pValue;

										printf("    [%lu] %20s: ", hObject, pkcs11_attribute_to_name(curr_attr->type));

										for (byte_idx = 0; byte_idx < curr_attr->ulValueLen; byte_idx++) {
											printf("%02x ", (unsigned int) pucValue[byte_idx]);
										}

										printf(";; %p/%lu\n", curr_attr->pValue, curr_attr->ulValueLen);

										break;
									case CKA_SUBJECT:
									case CKA_ISSUER:
										pucValue = curr_attr->pValue;

										printf("    [%lu] %20s: ", hObject, pkcs11_attribute_to_name(curr_attr->type));

										for (byte_idx = 0; byte_idx < curr_attr->ulValueLen; byte_idx++) {
											printf("\\x%02x", (unsigned int) pucValue[byte_idx]);
										}

										printf(" ;; %p/%lu\n", curr_attr->pValue, curr_attr->ulValueLen);

										break;
									
									default:
										printf("    [%lu] %20s: %p/%lu\n", hObject, pkcs11_attribute_to_name(curr_attr->type), curr_attr->pValue, curr_attr->ulValueLen);

										break;
								}
							} else {
								printf("    [%lu] %20s: (not found)\n", hObject, pkcs11_attribute_to_name(curr_attr->type));
							}

							free(curr_attr->pValue);
							curr_attr->pValue = NULL;
						}
					} else {
						printf("GetAttributeValue()/2 failed.\n");
					}
				} else {
					printf("GetAttributeValue(hObject=%lu)/1 failed (rv = %lu).\n", (unsigned long) hObject, (unsigned long) chk_rv);
				}

			}

			chk_rv = C_FindObjectsFinal(hSession);
			if (chk_rv != CKR_OK) {
				printf("FindObjectsFinal() failed.\n");
			}
		} else {
			printf("FindObjectsInit() failed.\n");
		}

		printf("--- Operations ---\n");

		for (currPrivKey = privateKeyObjects_root; *currPrivKey != CK_INVALID_HANDLE; currPrivKey++) {
			chk_rv = C_SignInit(hSession, &mechanism, *currPrivKey);
			if (chk_rv == CKR_OK) {
				signature_len = sizeof(signature);

				chk_rv = C_Sign(hSession, (CK_BYTE_PTR) "Test", strlen("Test"), (CK_BYTE_PTR) &signature, &signature_len);
				if (chk_rv == CKR_OK) {
					printf("[%04lu/%02lx] Signature: ", (unsigned long) *currPrivKey, (unsigned long) mechanism.mechanism);

					for (byte_idx = 0; byte_idx < signature_len; byte_idx++) {
						printf("%02x ", (unsigned int) signature[byte_idx]);
					}

					printf("\n");
				} else {
					printf("Sign() failed.\n");
				}
			} else {
				printf("SignInit() failed.\n");
			}
		}

		for (currPrivKey = privateKeyObjects_root; *currPrivKey != CK_INVALID_HANDLE; currPrivKey++) {
			chk_rv = C_EncryptInit(hSession, &mechanism, *currPrivKey);
			if (chk_rv == CKR_OK) {
				encrypted_buflen = sizeof(encrypted_buf);

				chk_rv = C_Encrypt(hSession, (CK_BYTE_PTR) "Test", strlen("Test"), encrypted_buf, &encrypted_buflen);
				if (chk_rv == CKR_OK) {
					printf("[%04lu/%02lx] Encrypted(Test): ", (unsigned long) *currPrivKey, (unsigned long) mechanism.mechanism);

					for (byte_idx = 0; byte_idx < encrypted_buflen; byte_idx++) {
						printf("%02x ", (unsigned int) encrypted_buf[byte_idx]);
					}

					printf("\n");
				} else {
					printf("Encrypt() failed.\n");
				}
			} else {
				printf("EncryptInit() failed.\n");
			}
		}

		for (currPrivKey = privateKeyObjects_root; *currPrivKey != CK_INVALID_HANDLE; currPrivKey++) {
			chk_rv = C_DecryptInit(hSession, &mechanism, *currPrivKey);
			if (chk_rv == CKR_OK) {
				decrypted_buflen = sizeof(decrypted_buf);

				chk_rv = C_Decrypt(hSession, (CK_BYTE_PTR) "\x4c\x36\x0f\x86\x2d\xb7\xb2\x46\x92\x11\x7e\x5f\xd1\xeb\x2c\xb0\xdb\x34\x60\xb8\x0c\xf8\x27\xb5\xfb\xce\xd1\xf4\x58\xa3\x20\x52\x9d\x97\x08\xd8\x2b\x5e\xb2\x37\x46\x72\x45\x7c\x66\x23\x53\xb5\xa5\x16\x61\x96\xbc\x5c\x8d\x85\x18\x24\xcf\x74\x7f\xc2\x23\x15\xd6\x42\x72\xa5\x2b\x29\x29\x1d\xa6\xea\x2b\xcb\x57\x59\xb3\x5f\xe2\xf8\x30\x12\x2f\x1b\xfa\xbd\xa9\x19\xef\x5c\xbb\x48\xdc\x28\x42\xdd\x90\xbe\x63\xeb\x59\x0c\xaf\x59\xcb\xe4\x6a\xf2\x56\x24\x41\xc2\x77\x7b\xc9\xf8\x02\x0f\x67\x3d\x2a\x98\x91\x14\xa2\x57", 128, decrypted_buf, &decrypted_buflen);
				if (chk_rv == CKR_OK) {
					printf("[%04lu/%02lx] Decrypted(It works!): ", (unsigned long) *currPrivKey, (unsigned long) mechanism.mechanism);

					for (byte_idx = 0; byte_idx < decrypted_buflen; byte_idx++) {
						printf("%02x ", (unsigned int) decrypted_buf[byte_idx]);
					}

					printf("\n");
				} else {
					printf("Decrypt() failed.\n");
				}
			} else {
				printf("DecryptInit() failed.\n");
			}
		}

		chk_rv = C_CloseSession(hSession);
		if (chk_rv != CKR_OK) {
			printf("CloseSession failed.\n");
		}
	} else {
		printf("OpenSession failed.\n");
	}

	C_Finalize(NULL);

	if (slots) {
		free(slots);
	}

	if (privateKeyObjects_root) {
		free(privateKeyObjects_root);
	}

	return(0);
}

int main(void) {
	int retval = 0, ck_retval;

	printf("Testing libcoolkey...\n");

	ck_retval = main_pkcs11();

	if (ck_retval != 0) {
		retval = ck_retval;
	}

	printf("Testing libcoolkey... DONE. Status = %i\n", ck_retval);

	return(retval);
}
